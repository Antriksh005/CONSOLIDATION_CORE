# Run Demo

From this folder:

```powershell
python tools\run_demo.py
```

Expected result:

```text
ok=true raw_events=550 groups=6 payment_support=500 decoy_mixed=0
```

Meaning:

- `raw_events` is the number of original log lines.
- `groups` is the number of compressed memory families.
- `top_group_support` shows repeated payment incident events merged together.
- `decoy_mixed_into_payment = 0` means unrelated noise was kept separate.

Generated files:

```text
reports/payment_incident_report.md
reports/runtime_metrics.md
```

To create your own experiment, edit:

```text
tools/generate_payment_incident_dataset.py
src/consolidation_core.cpp
```

See [CONFIGURATION.md](CONFIGURATION.md) for the exact knobs.
