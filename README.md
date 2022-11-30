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

## ADC

`analogSetAttenuation`: The maximum voltage is limited by VDD_A

- 0dB attenuaton (ADC_ATTEN_DB_0) gives full-scale voltage 1.1V
- 2.5dB attenuation (ADC_ATTEN_DB_2_5) gives full-scale voltage 1.5V
- 6dB attenuation (ADC_ATTEN_DB_6) gives full-scale voltage 2.2V
- 11dB attenuation (ADC_ATTEN_DB_11) gives full-scale voltage 3.9V

`analogReadResolution`: The analogReadResolution() function sets the number of bits used for the analog to digital conversion (ADC) on the ESP32. The ESP32 has a 12-bit ADC, so the resolution can be set between 9 and 12 bits.

- 9 bits (ADC_WIDTH_BIT_9) gives an output range of 0 to 511 inclusive
- 10 bits (ADC_WIDTH_BIT_10) gives an output range of 0 to 1023 inclusive
- 11 bits (ADC_WIDTH_BIT_11) gives an output range of 0 to 2047 inclusive
- 12 bits (ADC_WIDTH_BIT_12) gives an output range of 0 to 4095 inclusive

Constants used are part of `<esp_adc_cal.h>`. Values:

- `ADC_ATTEN_DB_0`: `0`
- `ADC_ATTEN_DB_2_5`: `1`
- `ADC_ATTEN_DB_6`: `2`
- `ADC_ATTEN_DB_11`: `3`
- `ADC_WIDTH_BIT_9`: `0`
- `ADC_WIDTH_BIT_10`: `1`
- `ADC_WIDTH_BIT_11`: `2`
- `ADC_WIDTH_BIT_12`: `3`

More info:

```c
/*
analogReadResolution(12);             // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
analogSetWidth(12);                   // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
                                      //  9-bit gives an ADC range of 0-511
                                      // 10-bit gives an ADC range of 0-1023
                                      // 11-bit gives an ADC range of 0-2047
                                      // 12-bit gives an ADC range of 0-4095
analogSetCycles(8);                   // Set number of cycles per sample, default is 8 and provides an optimal result, range is 1 - 255
analogSetSamples(1);                  // Set number of samples in the range, default is 1, it has an effect on sensitivity has been multiplied
analogSetClockDiv(1);                 // Set the divider for the ADC clock, default is 1, range is 1 - 255
analogSetAttenuation(ADC_11db);       // Sets the input attenuation for ALL ADC inputs, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
analogSetPinAttenuation(VP,ADC_11db); // Sets the input attenuation, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
                                      // ADC_0db provides no attenuation so IN/OUT = 1 / 1 an input of 3 volts remains at 3 volts before ADC measurement
                                      // ADC_2_5db provides an attenuation so that IN/OUT = 1 / 1.34 an input of 3 volts is reduced to 2.238 volts before ADC measurement
                                      // ADC_6db provides an attenuation so that IN/OUT = 1 / 2 an input of 3 volts is reduced to 1.500 volts before ADC measurement
                                      // ADC_11db provides an attenuation so that IN/OUT = 1 / 3.6 an input of 3 volts is reduced to 0.833 volts before ADC measurement
adcAttachPin(VP);                     // Attach a pin to ADC (also clears any other analog mode that could be on), returns TRUE/FALSE result
adcStart(VP);                         // Starts an ADC conversion on attached pin's bus
adcBusy(VP);                          // Check if conversion on the pin's ADC bus is currently running, returns TRUE/FALSE result
adcEnd(VP);                           // Get the result of the conversion (will wait if it have not finished), returns 16-bit integer result
*/
```

See [this](https://github.com/G6EJD/ESP32-ADC-Accuracy-Improvement-function/blob/master/ESP32_ADC_Read_Voltage_Accurate.ino).

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
