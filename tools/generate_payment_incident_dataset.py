from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "samples" / "payment_incident_logs.txt"


def main() -> None:
    OUT.parent.mkdir(parents=True, exist_ok=True)
    payment_templates = [
        "timeout while charging card",
        "gateway slow during checkout",
        "checkout failed after payment wait",
        "payment request exceeded latency budget",
        "retry issued after gateway timeout",
    ]
    decoys = [
        ("frontend", "css_asset_missing", "stylesheet returned 404"),
        ("email", "email_bounce", "user inbox rejected message"),
        ("profile", "avatar_cache_miss", "avatar image not in cache"),
        ("marketing", "pixel_timeout", "analytics pixel delayed"),
        ("search", "index_lag", "search index refresh delayed"),
    ]

    lines = []
    for i in range(500):
        text = payment_templates[i % len(payment_templates)]
        lines.append(
            "category=incident service=checkout root=payment_gateway_timeout "
            f"event_id=pay_{i:04d} latency_ms={900 + (i % 180)} message={text}"
        )

    for i in range(50):
        service, root, msg = decoys[i % len(decoys)]
        lines.append(
            f"category=decoy service={service} root={root} "
            f"event_id=decoy_{i:04d} message={msg}"
        )

    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"wrote {OUT} lines={len(lines)}")


if __name__ == "__main__":
    main()

