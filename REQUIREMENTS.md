# Requirements

This demo is intentionally small and local.

It does not require:

- cloud APIs
- LLM keys
- Docker
- databases
- npm
- Python packages

## Required

### 1. Python 3

Used only to generate the sample dataset and run the demo script.

Check:

```powershell
python --version
```

Recommended:

```text
Python 3.10 or newer
```

### 2. C++ Compiler

The demo compiles `src/consolidation_core.cpp` into a local executable.

On Windows, the easiest option is MinGW g++.

Check:

```powershell
g++ --version
```

If `g++` is not found, install MinGW/MSYS2 or another C++17 compiler and make sure `g++` is available in `PATH`.

## Hardware

This demo is intentionally tiny.

Expected laptop impact:

```text
CPU: brief compile/run burst
RAM: small process footprint
Disk: less than a few MB for source, sample data, executable, and reports
Network: none
```

The current runner records local runtime and file-size metrics in:

```text
reports/runtime_metrics.md
```

On Windows, the C++ engine records its own peak working set in the generated
report. The demo itself does not allocate large models, indexes, or databases.

## Run

```powershell
python tools\run_demo.py
```

Expected output shape:

```text
ok=true raw_events=550 groups=6 payment_support=500 decoy_mixed=0
```

## Output

The generated report is written to:

```text
reports/payment_incident_report.md
```

## Notes

This repository is a public proof of the consolidation layer only.

It is not the full Crystal runtime.
