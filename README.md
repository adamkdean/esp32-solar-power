# esp8266 solar power

Solar power project with esp8266.

## Todo

- [x] Connect to WiFi
- [x] Read battery voltage (3.8v max reduced to 1v via voltage divider)
- [x] Post voltage reading to electronics-api
- [ ] Connect solar panels
- [ ] Collect readings

## Notes

The file `firmware/config.h` is ignored with `git update-index --assume-unchanged` so that SSID credentials are not committed to the repo.
