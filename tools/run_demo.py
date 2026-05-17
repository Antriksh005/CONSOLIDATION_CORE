import subprocess
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src" / "consolidation_core.cpp"
EXE = ROOT / "build" / "consolidation_core.exe"
DATA = ROOT / "samples" / "payment_incident_logs.txt"
REPORT = ROOT / "reports" / "payment_incident_report.md"
METRICS = ROOT / "reports" / "runtime_metrics.md"


def run(cmd: list[str]) -> None:
    print("+", " ".join(str(c) for c in cmd))
    subprocess.run(cmd, cwd=ROOT, check=True)


def run_capture(cmd: list[str]) -> tuple[str, float]:
    print("+", " ".join(str(c) for c in cmd))
    start = time.perf_counter()
    completed = subprocess.run(
        cmd,
        cwd=ROOT,
        check=True,
        text=True,
        capture_output=True,
    )
    elapsed = (time.perf_counter() - start) * 1000.0
    if completed.stdout:
        print(completed.stdout.strip())
    if completed.stderr:
        print(completed.stderr.strip())
    return completed.stdout.strip(), elapsed


def main() -> None:
    (ROOT / "build").mkdir(exist_ok=True)
    (ROOT / "reports").mkdir(exist_ok=True)

    run(["python", str(ROOT / "tools" / "generate_payment_incident_dataset.py")])
    run(["g++", "-std=c++17", "-O2", str(SRC), "-o", str(EXE), "-lpsapi"])
    output, wall_ms = run_capture([str(EXE), str(DATA), str(REPORT)])

    exe_size = EXE.stat().st_size if EXE.exists() else 0
    input_size = DATA.stat().st_size if DATA.exists() else 0
    report_size = REPORT.stat().st_size if REPORT.exists() else 0

    METRICS.write_text(
        "\n".join(
            [
                "# Runtime Metrics",
                "",
                "| Metric | Value |",
                "| --- | ---: |",
                f"| Runner wall time | {wall_ms:.3f} ms |",
                f"| Input file size | {input_size} bytes |",
                f"| Report file size | {report_size} bytes |",
                f"| Compiled executable size | {exe_size} bytes |",
                "| External services | 0 |",
                "| Cloud/API calls | 0 |",
                "| Python packages installed | 0 |",
                "",
                "## Engine Output",
                "",
                "```text",
                output,
                "```",
                "",
                "## Notes",
                "",
                "- These numbers are from the local machine that generated this report.",
                "- Engine runtime and peak working set can vary by CPU, compiler, OS, and background load.",
                "- On Windows, the C++ engine reports `peak_working_set_kb` from the process itself.",
                "- No cloud/API services are used.",
                "",
            ]
        ),
        encoding="utf-8",
    )

    print()
    print(f"report: {REPORT}")
    print(f"metrics: {METRICS}")
    print(REPORT.read_text(encoding="utf-8").split("## Groups", 1)[0])


if __name__ == "__main__":
    main()
