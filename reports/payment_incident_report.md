# Crystal Consolidation Core Report

| Metric | Value |
| --- | ---: |
| Raw events | 550 |
| Memory groups | 6 |
| Compression ratio | 91.67x |
| Payment group support | 500 |
| Decoys mixed into payment evidence | 0 |
| Runtime | 31.200 ms |

## Groups

### payment_gateway_timeout

- support_count: 500
- anchor_count: 1377
- evidence:
  - `category=incident service=checkout root=payment_gateway_timeout event_id=pay_0000 latency_ms=900 message=timeout while charging card`
  - `category=incident service=checkout root=payment_gateway_timeout event_id=pay_0001 latency_ms=901 message=gateway slow during checkout`
  - `category=incident service=checkout root=payment_gateway_timeout event_id=pay_0002 latency_ms=902 message=checkout failed after payment wait`
  - `category=incident service=checkout root=payment_gateway_timeout event_id=pay_0003 latency_ms=903 message=payment request exceeded latency budget`
  - `category=incident service=checkout root=payment_gateway_timeout event_id=pay_0004 latency_ms=904 message=retry issued after gateway timeout`

### css_asset_missing

- support_count: 10
- anchor_count: 29
- evidence:
  - `category=decoy service=frontend root=css_asset_missing event_id=decoy_0000 message=stylesheet returned 404`
  - `category=decoy service=frontend root=css_asset_missing event_id=decoy_0005 message=stylesheet returned 404`
  - `category=decoy service=frontend root=css_asset_missing event_id=decoy_0010 message=stylesheet returned 404`
  - `category=decoy service=frontend root=css_asset_missing event_id=decoy_0015 message=stylesheet returned 404`
  - `category=decoy service=frontend root=css_asset_missing event_id=decoy_0020 message=stylesheet returned 404`

### email_bounce

- support_count: 10
- anchor_count: 29
- evidence:
  - `category=decoy service=email root=email_bounce event_id=decoy_0001 message=user inbox rejected message`
  - `category=decoy service=email root=email_bounce event_id=decoy_0006 message=user inbox rejected message`
  - `category=decoy service=email root=email_bounce event_id=decoy_0011 message=user inbox rejected message`
  - `category=decoy service=email root=email_bounce event_id=decoy_0016 message=user inbox rejected message`
  - `category=decoy service=email root=email_bounce event_id=decoy_0021 message=user inbox rejected message`

### avatar_cache_miss

- support_count: 10
- anchor_count: 29
- evidence:
  - `category=decoy service=profile root=avatar_cache_miss event_id=decoy_0002 message=avatar image not in cache`
  - `category=decoy service=profile root=avatar_cache_miss event_id=decoy_0007 message=avatar image not in cache`
  - `category=decoy service=profile root=avatar_cache_miss event_id=decoy_0012 message=avatar image not in cache`
  - `category=decoy service=profile root=avatar_cache_miss event_id=decoy_0017 message=avatar image not in cache`
  - `category=decoy service=profile root=avatar_cache_miss event_id=decoy_0022 message=avatar image not in cache`

### pixel_timeout

- support_count: 10
- anchor_count: 29
- evidence:
  - `category=decoy service=marketing root=pixel_timeout event_id=decoy_0003 message=analytics pixel delayed`
  - `category=decoy service=marketing root=pixel_timeout event_id=decoy_0008 message=analytics pixel delayed`
  - `category=decoy service=marketing root=pixel_timeout event_id=decoy_0013 message=analytics pixel delayed`
  - `category=decoy service=marketing root=pixel_timeout event_id=decoy_0018 message=analytics pixel delayed`
  - `category=decoy service=marketing root=pixel_timeout event_id=decoy_0023 message=analytics pixel delayed`

### index_lag

- support_count: 10
- anchor_count: 28
- evidence:
  - `category=decoy service=search root=index_lag event_id=decoy_0004 message=search index refresh delayed`
  - `category=decoy service=search root=index_lag event_id=decoy_0009 message=search index refresh delayed`
  - `category=decoy service=search root=index_lag event_id=decoy_0014 message=search index refresh delayed`
  - `category=decoy service=search root=index_lag event_id=decoy_0019 message=search index refresh delayed`
  - `category=decoy service=search root=index_lag event_id=decoy_0024 message=search index refresh delayed`

