// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <string>
#include "../../../config.h"
#include "api.h"

int uploadBatteryVoltage(WiFiClient client, float voltage) {
  char payload[20];
  snprintf(payload, sizeof(payload), "{\"voltage\":%.3f}", voltage);

  char url[] = { API_URL "/battery" };
  char bearerToken[] = { "Bearer " API_BEARER_TOKEN };

  Serial.println("Uploading battery voltage payload:" + String(payload));

  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Authorization", bearerToken);
  http.addHeader("Content-Type", "application/json");
  int httpStatus = http.POST(payload);

  Serial.println("HTTP status: " + String(httpStatus));

  return httpStatus;
}
