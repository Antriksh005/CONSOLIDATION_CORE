# Configuration And Experiment Guide

This repo is intentionally small, so the main knobs are visible in the files.

## 1. Change The Input Data

Edit:

```text
samples/payment_incident_logs.txt
```

Each line is one event.

Recommended shape:

```text
category=incident service=checkout root=payment_gateway_timeout event_id=pay_0001 message=gateway slow during checkout
```

Important fields:

| Field | Meaning |
| --- | --- |
| `category` | Use `incident` for main data and `decoy` for unrelated noise. |
| `service` | System area, for example `checkout`, `email`, `frontend`. |
| `root` | The underlying incident family you expect events to belong to. |
| `event_id` | Unique event identifier. |
| `message` | Human-readable event text. |

The engine can read other text too, but these fields make the proof easier to inspect.

## 2. Change The Generated Dataset

Edit:

```text
tools/generate_payment_incident_dataset.py
```

Useful knobs:

```python
for i in range(500):  # main incident event count
for i in range(50):   # decoy event count
```

You can also edit:

```python
payment_templates
decoys
```

This lets you test harder noise, more decoys, or a different domain.

## 3. Change Merge Strictness

Edit:

```text
src/consolidation_core.cpp
```

Main threshold:

```cpp
if (best >= 0 && best_score >= 0.55)
```

Lower value:

```text
more aggressive merging, higher risk of wrong groups
```

Higher value:

```text
stricter merging, more groups, lower risk of pollution
```

## 4. Change Hard-Rejection Rules

Edit:

```cpp
for (const auto& key : {"root", "service", "category"})
```

These fields are treated as structural boundaries. If they conflict, the event
cannot merge into that group.

For example, this prevents:

```text
service=email
```

from merging into:

```text
service=checkout
```

## 5. What To Watch In The Report

After running:

```powershell
python tools\run_demo.py
```

Check:

```text
reports/payment_incident_report.md
reports/runtime_metrics.md
```

Important signals:

| Metric | Good Sign |
| --- | --- |
| `Payment group support` | Main repeated incident merged correctly. |
| `Decoys mixed into payment evidence` | Should stay `0`. |
| `Memory groups` | Should be much lower than raw events, but not `1`. |
| `Compression ratio` | Shows noise reduction. |
| `Peak working set` | Shows RAM footprint on Windows. |

