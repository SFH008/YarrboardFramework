# v2.5.0

## Features

- Added static IP address support for network configuration
- Added `onConfigUpdatedHook()` virtual function to `BaseChannel`, called in `ChannelController::handleConfigCommand` to simplify config change handling in channels
- Added `setWindow()` method to `RollingAverage`

## Improvements

- Separated active and passive buzzer melodies; added morse characters to active buzzer melody list

## Bug Fixes

- `NavicoController` now respects the `app_enable_mfd` configuration option