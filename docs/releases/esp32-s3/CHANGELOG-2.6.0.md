# v2.6.0

## Features

- Added `page.setBadge()` and `page.clearBadge()` methods to display Bootstrap badge indicators on navbar entries
- Added support for URL-based changelogs in `ota_manifest.json` — changelog field can now point to a remote markdown file instead of inline text
- Changelog is now written to a separate per-board markdown file and linked in `ota_manifest.json`
- Added `ota_complete` message handling for cleaner post-update UI flow

## Improvements

- System page config is now refreshed automatically when the system page is opened

## Bug Fixes

- Fixed OTA progress not completing cleanly when firmware update finishes (fixes #4)
- Fixed `ota_manifest.json` not linking to separate changelog files (fixes #3)