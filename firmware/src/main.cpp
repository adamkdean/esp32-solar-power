// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <WiFi.h>
#include "lib/api/api.h"
#include "lib/led/led.h"
#include "lib/wifi/wifi.h"
#include "../config.h"
#include "main.h"

#define ADC_TO_VOLTAGE 0.0037939453125

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  mblink(10, 50, 50);
  connect_to_wifi();
}

void loop() {
  WiFiClient client;

  // Ensure the WiFi is connected
  if (WiFi.status() != WL_CONNECTED) connect_to_wifi();

  // Gather battery voltage
  char readings[64];
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * ADC_TO_VOLTAGE;
  sprintf(readings, "Sensor value: %d, voltage: %f", sensorValue, voltage);
  Serial.println(readings);

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
