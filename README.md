# Crystal Consolidation Core

Minimal public proof of Crystal's deterministic consolidation layer.

The demo takes noisy operational events and compresses them into evidence-backed
memory groups without LLMs, cloud APIs, databases, or vector search.

```text
550 raw events -> 6 memory groups -> 91.67x compression -> 0 decoy pollution
```

This is not the full Crystal runtime. It does not include temporal paths, proof
gates, supervisor logic, private research internals, or any LLM.

## Why This Exists

Most systems either store logs as raw lines, search them by keywords, or send
them into a model. This small repo shows a simpler primitive:

```text
observe repeated events
-> extract stable anchors
-> merge structurally compatible events
-> reinforce the group
-> keep source evidence
-> reject unrelated decoys
```

## Verified Demo Result

Latest local run:

| Metric | Value |
| --- | ---: |
| Raw events | 550 |
| Memory groups | 6 |
| Compression ratio | 91.67x |
| Main incident support | 500 |
| Decoys mixed into main incident | 0 |
| Engine runtime | recorded in the generated report |
| Peak RAM | recorded in the generated report on Windows |

See the generated report:

```text
reports/payment_incident_report.md
```

Runtime/file-size metrics:

```text
reports/runtime_metrics.md
```

To change the dataset, merge threshold, or hard-rejection fields, see:

```text
CONFIGURATION.md
```

## Research Roadmap

This repo is Layer 1 of the public Crystal research path.

The next public proof layers are temporal association, simplicity selection,
bounded curiosity, and embodied feedback.

See [RESEARCH_PATH.md](RESEARCH_PATH.md).

## Run

Requirements are listed in [REQUIREMENTS.md](REQUIREMENTS.md).

```powershell
python tools\run_demo.py
```

The script:

```text
1. generates a deterministic noisy payment incident dataset
2. compiles src/consolidation_core.cpp with g++
3. runs the C++ engine
4. writes an evidence-backed report
```

Expected output:

```text
ok=true raw_events=550 groups=6 payment_support=500 decoy_mixed=0
```

## What It Proves

- Repeated noisy events can collapse into one reinforced group.
- The group keeps original evidence lines.
- Decoy events with similar words stay separate when structural fields conflict.
- The result is deterministic and locally reproducible.

## What It Does Not Prove

- It is not a full incident-management product.
- It is not a replacement for observability platforms.
- It is not an LLM memory system.
- It does not yet include temporal reasoning or proof gates.

## Core Flow

```text
read event
-> parse fields and anchors
-> compare with known memory groups
-> reject hard conflicts
-> merge if similarity passes threshold
-> otherwise create a new group
-> write report with evidence
```

## License

This repository is source-available for evaluation and research.

You may read, run, and test the demo locally. Commercial use, production use,
hosted services, resale, or product embedding require written permission.

See [LICENSE](LICENSE) and [LICENSE_NOTE.md](LICENSE_NOTE.md).
