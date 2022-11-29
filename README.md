# esp8266 solar power

Solar power project with esp32 (specifically `ESP32-WROOM-32 (Node-MCU-32S)`).

For the `ESP32-WROOM-32 (Node-MCU-32S)` the FQBN is `esp32:esp32:nodemcu-32s`.

## Todo

- [x] Deploy firmware
- [x] Connect to WiFi
- [ ] Read battery box 1 voltage (3.8v max reduced to 1v via voltage divider)
- [ ] Read battery box 2 voltage (3.8v max reduced to 1v via voltage divider)
- [ ] Read solar voltage 1 (5v max reduced to 1v via voltage divider)
- [ ] Read solar voltage 2 (5v max reduced to 1v via voltage divider)
- [ ] Post voltage readings to electronics-api
- [ ] Connect solar panels
- [ ] Collect readings

## Setup

Add the esp32 board manager to `/Users/<user>/Library/Arduino15/arduino-cli.yaml`:

```
board_manager:
  additional_urls:
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Be sure to install esp32 platform `arduino-cli core install esp32:esp32`.

## Notes

The file `firmware/config.h` is ignored with `git update-index --assume-unchanged` so that SSID credentials are not committed to the repo.
