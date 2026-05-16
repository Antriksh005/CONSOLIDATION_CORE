# Run Demo

From this folder:

```powershell
python tools\run_demo.py
```

Expected result:

```text
raw_events: 550
groups: around 6-10
top_group_support: 500
decoy_mixed_into_payment: 0
```

Meaning:

- `raw_events` is the number of original log lines.
- `groups` is the number of compressed memory families.
- `top_group_support` shows repeated payment incident events merged together.
- `decoy_mixed_into_payment = 0` means unrelated noise was kept separate.

