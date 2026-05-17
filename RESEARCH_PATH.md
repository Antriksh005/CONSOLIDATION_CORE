# Crystal Public Research Path

Crystal is being released as small public proof layers.

This repository is **Layer 1**. It proves deterministic consolidation:

```text
noisy events -> reinforced memory groups -> evidence-backed report
```

The public repos are proof slices. They are not the complete private research
runtime.

## Layer 1: Consolidation Core

Status: public

Proof:

```text
550 noisy events -> 6 memory groups
500 related incident events -> one reinforced group
0 decoy events mixed into the main incident group
```

What it demonstrates:

- repeated signals can reinforce one memory family;
- unrelated decoys can be separated;
- output remains inspectable through source evidence.

## Layer 2: Temporal Association

Status: planned public proof

Goal:

```text
event A -> event B -> event C
```

This layer will show how a local memory system can store source-backed event
paths instead of only storing isolated groups.

Example:

```text
db_pool_exhaustion -> retry_storm -> checkout_failure
```

## Layer 3: Simplicity Selection

Status: planned public proof

Goal:

```text
when multiple explanations fit, prefer the simplest valid one
```

This layer will demonstrate a small rule-selection benchmark where complex
explanations are rejected when a simpler valid explanation exists.

## Layer 4: Bounded Curiosity

Status: planned public proof

Goal:

```text
idle time -> candidate pattern proposals -> no automatic truth claims
```

This layer will show how a system can propose possible links from stored memory
while keeping them marked as candidates until evidence validates them.

## Layer 5: Embodied Feedback

Status: planned public proof

Goal:

```text
memory affects action inside a controlled simulation
```

This layer will connect memory outputs to a small environment where behavior can
be tested through repeatable runs.

## Boundary

Crystal is not being presented as consciousness, AGI, or a replacement for
modern AI systems.

The research question is narrower:

```text
Can machines have a useful local memory substrate that consolidates experience,
keeps evidence, tracks temporal structure, and improves future behavior?
```

