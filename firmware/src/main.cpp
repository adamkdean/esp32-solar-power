// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <esp_adc_cal.h>
#include <WiFi.h>
#include "lib/api/api.h"
#include "lib/led/led.h"
#include "lib/wifi/wifi.h"
#include "../config.h"
#include "main.h"

#define REF_VOLTAGE 1.1                   // 1.1V reference voltage, ADC_0db
#define ADC_UNITS 2047                    // 12-bit ADC, ADC_WIDTH_BIT_11 (0-2047)
#define ADC_RESOLUTION 11                 // ADC width (11-bit, 0-2047)
#define ADC_ATTEN ADC_0db                 // ADC attenuation (0dB, 0-1.1V)
#define ADC_TO_V REF_VOLTAGE / ADC_UNITS  // ADC to voltage conversion (V per ADC unit)
#define ADC1_CH4 A4                       // ADC1 channel 4 (GPIO32)
#define ADC1_CH5 A5                       // ADC1 channel 5 (GPIO33)
#define ADC1_CH6 A6                       // ADC1 channel 6 (GPIO34)
#define ADC1_CH7 A7                       // ADC1 channel 7 (GPIO35)

// The voltage divider is based on a theoretical max 3.9V
// supply voltage reduced down to 0-1.0V range for the ADC.
#define V_DIV_R1 2772                     // Ohms, voltage divider R1
#define V_DIV_R2 988                      // Ohms, voltage divider R2
#define V_DIV_FACTOR 3.805                // Voltage divider, (V_DIV_R1 + V_DIV_R2) / V_DIV_R2
#define V_CALIBRATION 0.985               // Adjustment for device calibration

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  analogReadResolution(ADC_RESOLUTION);
  analogSetAttenuation(ADC_ATTEN);
  connect_to_wifi();
}

void loop() {
  WiFiClient client;

  // Ensure the WiFi is still connected
  if (WiFi.status() != WL_CONNECTED) connect_to_wifi();

  // Gather battery voltage
  int sensorValue = analogRead(ADC1_CH4);
  float voltage = sensorValue * ADC_TO_V;
  float actualVoltage = voltage * V_DIV_FACTOR * V_CALIBRATION;
  Serial.println("Sensor value: " + String(sensorValue) + ", voltage: " + String(voltage) + ", actual voltage: " + String(actualVoltage));

  // Upload battery voltage
  int status = uploadBatteryVoltage(client, voltage);
  if (status == 200) {
    Serial.println("Battery voltage uploaded successfully");
    mblink(10, 50, 50);
  } else {
    Serial.println("Battery voltage upload failed");
    blink(500, 500);
  }
}
