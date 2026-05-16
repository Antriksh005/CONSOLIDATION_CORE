# Crystal Consolidation Core

This is the first small public proof layer of Crystal.

It demonstrates one idea:

```text
many noisy events -> fewer reinforced memory groups -> evidence-backed report
```

This is not the full Crystal runtime. It does not include temporal paths,
proof gates, supervisor logic, private research internals, or any LLM.

## What This Demo Shows

- Raw operational events can be compressed into incident groups.
- Repeated events reinforce the same group through `support_count`.
- Unrelated decoy events stay separated instead of polluting the main group.
- Every group keeps evidence samples so the result is inspectable.

## Run

```powershell
python tools\run_demo.py
```

The report is written to:

```text
reports/payment_incident_report.md
```

## Learning Shape

The C++ engine does this:

```text
read event
-> extract anchors
-> compare against existing memory groups
-> merge if structurally compatible
-> otherwise create a new group
-> write evidence-backed report
```

