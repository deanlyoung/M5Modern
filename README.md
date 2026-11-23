# M5Modern

M5Modern is a work-in-progress, original M5Paper application platform derived from [dethlex/PaperOS](https://github.com/dethlex/PaperOS). Its goal is to retain PaperOS's modular application architecture while migrating its hardware and display stack from M5EPD to M5Unified and M5GFX.

**Status: early migration.** The default `m5modern` target runs an experimental M5Unified launcher with a persistent counter, system monitor, calculator, local clock, timer, and Wi-Fi scanner. The launcher, counter, and system monitor have had an initial touch check on an original M5Paper; the other apps still need device-level checks. The timer displays minutes and seconds and only runs while its screen is open; it does not yet sound an alarm. The clock is manually set and is not network-synchronized. Sleep and power management are not yet implemented in this target; use USB power during development. The inherited `m5paper` target still uses M5EPD. [UPSTREAM_README.md](UPSTREAM_README.md) describes the original project, not completed M5Modern features.

## Intended initial apps

Calculator, notes, clock, timer, system monitor, Wi-Fi analyzer, BLE inspector, tap counter, Home Assistant dashboard, plain-text reader, weather, and games. EPUB, Aranet4, and Awair local dashboards are later work. The inherited calendar, file server and printer applications are not registered in the launcher; their source remains upstream material pending removal or restructuring.

## Transport security during migration

The inherited HTTP client has been changed to require HTTPS and certificate validation, but it has not yet been connected to the new M5Unified application. Once integrated, it expects PEM-encoded trusted CA certificates in `/paperos/ca.pem` on the microSD card; the device must have a correct clock and the server certificate must match its hostname. Missing trust material fails closed. A private Home Assistant CA can be included in this file. End-to-end network behavior is not yet verified. The original PaperOS config mirror includes secrets; do not publish it or expose it using an unauthenticated file server.

## Development

Use PlatformIO. `native` runs inherited logic tests and `native-modern` tests the migrated app switcher and calculator. `m5modern-probe` is a standalone hardware experiment. The original flash backup on the development Mac is not part of this repository.

```sh
pio test -e native
pio test -e native-modern
pio run -e m5modern
```

PaperOS is MIT licensed; its copyright and license are preserved in [LICENSE](LICENSE). Third-party assets and code retain their own licenses.
