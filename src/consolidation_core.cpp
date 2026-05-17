#include <algorithm>
#include <chrono>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

struct Event {
    std::string raw;
    std::map<std::string, std::string> fields;
    std::set<std::string> anchors;
};

struct MemoryGroup {
    std::string label;
    std::map<std::string, std::string> fields;
    std::set<std::string> anchors;
    int support = 0;
    std::vector<std::string> evidence;
};

static std::string lower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

static std::vector<std::string> split_words(const std::string& text) {
    std::vector<std::string> words;
    std::string cur;
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
            cur.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
        } else if (!cur.empty()) {
            words.push_back(cur);
            cur.clear();
        }
    }
    if (!cur.empty()) words.push_back(cur);
    return words;
}

static Event parse_event(const std::string& line) {
    Event e;
    e.raw = line;
    for (const auto& word : split_words(line)) {
        auto pos = word.find('_');
        if (pos != std::string::npos) e.anchors.insert(word);
    }

    std::istringstream in(line);
    std::string part;
    while (in >> part) {
        auto pos = part.find('=');
        if (pos == std::string::npos) continue;
        std::string key = lower(part.substr(0, pos));
        std::string value = lower(part.substr(pos + 1));
        e.fields[key] = value;
        e.anchors.insert(key + ":" + value);
        e.anchors.insert(value);
    }
    return e;
}

static bool hard_conflict(const Event& e, const MemoryGroup& g) {
    for (const auto& key : {"root", "service", "category"}) {
        auto a = e.fields.find(key);
        auto b = g.fields.find(key);
        if (a != e.fields.end() && b != g.fields.end() && a->second != b->second) return true;
    }
    return false;
}

static double similarity(const Event& e, const MemoryGroup& g) {
    if (hard_conflict(e, g)) return 0.0;

    int common = 0;
    for (const auto& a : e.anchors) {
        if (g.anchors.count(a)) common++;
    }
    const int total = static_cast<int>(e.anchors.size() + g.anchors.size() - common);
    if (total == 0) return 0.0;

    double score = static_cast<double>(common) / static_cast<double>(total);
    if (e.fields.count("root") && g.fields.count("root") && e.fields.at("root") == g.fields.at("root")) score += 0.45;
    if (e.fields.count("service") && g.fields.count("service") && e.fields.at("service") == g.fields.at("service")) score += 0.10;
    return std::min(score, 1.0);
}

static void merge(MemoryGroup& g, const Event& e) {
    g.support++;
    g.anchors.insert(e.anchors.begin(), e.anchors.end());
    for (const auto& kv : e.fields) {
        if (!g.fields.count(kv.first)) g.fields[kv.first] = kv.second;
    }
    if (g.evidence.size() < 5) g.evidence.push_back(e.raw);
}

static MemoryGroup make_group(const Event& e) {
    MemoryGroup g;
    auto root = e.fields.find("root");
    g.label = root == e.fields.end() ? "unknown_event_family" : root->second;
    g.fields = e.fields;
    g.anchors = e.anchors;
    merge(g, e);
    return g;
}

static long long peak_memory_kb() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS info;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info))) {
        return static_cast<long long>(info.PeakWorkingSetSize / 1024);
    }
#endif
    return -1;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: consolidation_core <input.txt> <report.md>\n";
        return 2;
    }

    auto start = std::chrono::steady_clock::now();
    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "could not open input\n";
        return 1;
    }

    std::vector<MemoryGroup> groups;
    std::string line;
    int raw_events = 0;

    while (std::getline(input, line)) {
        if (line.empty()) continue;
        raw_events++;
        Event e = parse_event(line);

        int best = -1;
        double best_score = 0.0;
        for (int i = 0; i < static_cast<int>(groups.size()); ++i) {
            double score = similarity(e, groups[i]);
            if (score > best_score) {
                best_score = score;
                best = i;
            }
        }

        if (best >= 0 && best_score >= 0.55) {
            merge(groups[best], e);
        } else {
            groups.push_back(make_group(e));
        }
    }

    std::sort(groups.begin(), groups.end(), [](const MemoryGroup& a, const MemoryGroup& b) {
        return a.support > b.support;
    });

    int payment_support = 0;
    int decoy_mixed = 0;
    for (const auto& g : groups) {
        bool payment_group = g.label == "payment_gateway_timeout";
        if (payment_group) payment_support = g.support;
        if (payment_group) {
            for (const auto& ev : g.evidence) {
                if (ev.find("category=decoy") != std::string::npos) decoy_mixed++;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    long long peak_kb = peak_memory_kb();

    std::ofstream report(argv[2]);
    report << "# Crystal Consolidation Core Report\n\n";
    report << "| Metric | Value |\n| --- | ---: |\n";
    report << "| Raw events | " << raw_events << " |\n";
    report << "| Memory groups | " << groups.size() << " |\n";
    report << "| Compression ratio | " << std::fixed << std::setprecision(2)
           << (groups.empty() ? 0.0 : static_cast<double>(raw_events) / groups.size()) << "x |\n";
    report << "| Payment group support | " << payment_support << " |\n";
    report << "| Decoys mixed into payment evidence | " << decoy_mixed << " |\n";
    report << "| Runtime | " << std::fixed << std::setprecision(3) << elapsed_ms << " ms |\n";
    if (peak_kb >= 0) report << "| Peak working set | " << peak_kb << " KB |\n";
    report << "\n";

    report << "## Groups\n\n";
    for (const auto& g : groups) {
        report << "### " << g.label << "\n\n";
        report << "- support_count: " << g.support << "\n";
        report << "- anchor_count: " << g.anchors.size() << "\n";
        report << "- evidence:\n";
        for (const auto& ev : g.evidence) report << "  - `" << ev << "`\n";
        report << "\n";
    }

    std::cout << "ok=true raw_events=" << raw_events
              << " groups=" << groups.size()
              << " payment_support=" << payment_support
              << " decoy_mixed=" << decoy_mixed
              << " runtime_ms=" << std::fixed << std::setprecision(3) << elapsed_ms
              << " peak_working_set_kb=" << peak_kb << "\n";
    return decoy_mixed == 0 && payment_support >= 500 ? 0 : 1;
}
