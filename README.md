# M5Modern

M5Modern is a work-in-progress, original M5Paper application platform derived from [dethlex/PaperOS](https://github.com/dethlex/PaperOS). Its goal is to retain PaperOS's modular application architecture while migrating its hardware and display stack from M5EPD to M5Unified and M5GFX.

**Status: early migration; not ready to install as M5Modern.** The default `m5paper` target is inherited from PaperOS and still uses M5EPD. The separate `m5modern-probe` target is only a hardware experiment; it does not contain the application launcher. No device behavior or battery life has yet been verified for the migration. The original project documentation is retained in [UPSTREAM_README.md](UPSTREAM_README.md) for reference and does not describe a completed M5Modern release.

## Intended initial apps

Calculator, notes, clock, timer, system monitor, Wi-Fi analyzer, BLE inspector, tap counter, Home Assistant dashboard, plain-text reader, weather, and games. EPUB, Aranet4, and Awair local dashboards are later work. The inherited calendar, file server and printer applications are not registered in the launcher; their source remains upstream material pending removal or restructuring.

## Transport security during migration

The inherited HTTP client has been changed to require HTTPS and certificate validation. Put PEM-encoded trusted CA certificates in `/paperos/ca.pem` on the microSD card; the device must have a correct clock and the server certificate must match its hostname. Missing trust material fails closed. A private Home Assistant CA can be included in this file. These changes are preliminary: end-to-end network behavior is not yet verified. The original PaperOS config mirror includes secrets; do not publish it or expose it using an unauthenticated file server.

## Development

Use PlatformIO. The `native` target runs inherited logic tests; the `m5modern-probe` target builds a standalone M5Unified framebuffer and touch probe. Do not upload the probe expecting the app suite. The original flash backup on the development Mac is not part of this repository.

```sh
pio test -e native
pio run -e m5modern-probe
```

PaperOS is MIT licensed; its copyright and license are preserved in [LICENSE](LICENSE). Third-party assets and code retain their own licenses.
