# Migration work

The experimental M5Unified shell is flashable but incomplete. Preserve upstream app lifecycle and tests while replacing direct M5EPD calls and canvas/font assumptions with M5Unified/M5GFX. Verify original M5Paper hardware on every stage.

- [x] Retain upstream history and attribution.
- [x] Disable registration of printer, calendar, and network file server apps.
- [x] Add fail-closed HTTPS trust policy (device integration testing pending).
- [ ] Validate the isolated M5Unified display and input probe on hardware. The probe flashed and reported a 540 x 960 screen and battery telemetry over serial; visual rendering and touch remain unverified.
- [x] Run the upstream app-switcher lifecycle with an M5Unified framebuffer, launcher, persistent counter and system monitor; initial touch check passed on hardware.
- [ ] Validate the new calculator, manually set clock, foreground-only timer, and Wi-Fi scanner on hardware. They compile, but their interaction and battery behavior remain unverified.
- [ ] Migrate display, touch, buttons, RTC, SD, sensors, battery, sleep/wake and fonts; preserve e-paper refresh and power behavior.
- [ ] Port launcher, settings, Home Assistant, reader, weather and games.
- [ ] Complete and validate calculator, notes, clock, timer, system monitor, Wi-Fi analyzer, BLE inspector and counter as discrete apps. Initial versions exist for all except notes and BLE inspector.
- [ ] Validate certificate trust, hostname mismatch, unavailable CA, network failures, time setup and Home Assistant interaction on device.
- [ ] Test actual e-paper redraws, touch, SD, persistence, sleep/wake, memory and battery behavior.
- [ ] Remove unused inherited apps and services and audit licenses when reusing other implementations.

Later: EPUB, Aranet4, and Awair local API dashboards.
