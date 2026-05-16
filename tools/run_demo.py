import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src" / "consolidation_core.cpp"
EXE = ROOT / "build" / "consolidation_core.exe"
DATA = ROOT / "samples" / "payment_incident_logs.txt"
REPORT = ROOT / "reports" / "payment_incident_report.md"


def run(cmd: list[str]) -> None:
    print("+", " ".join(str(c) for c in cmd))
    subprocess.run(cmd, cwd=ROOT, check=True)


def main() -> None:
    (ROOT / "build").mkdir(exist_ok=True)
    (ROOT / "reports").mkdir(exist_ok=True)

    run(["python", str(ROOT / "tools" / "generate_payment_incident_dataset.py")])
    run(["g++", "-std=c++17", "-O2", str(SRC), "-o", str(EXE)])
    run([str(EXE), str(DATA), str(REPORT)])

    print()
    print(f"report: {REPORT}")
    print(REPORT.read_text(encoding="utf-8").split("## Groups", 1)[0])


if __name__ == "__main__":
    main()

