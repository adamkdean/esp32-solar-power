// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <WiFi.h>
#include "../../../config.h"
#include "../led/led.h"
#include "wifi.h"

void connect_to_wifi() {
  char msg[64];
  sprintf(msg, "Connecting to %s with %s", WIFI_SSID, WIFI_PASSWORD);
  Serial.println(msg);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    sprintf(msg, "Connecting to %s with %s", WIFI_SSID, WIFI_PASSWORD);
    Serial.println(msg);

    sprintf(msg, "%s %s",
      wl_status_to_string(WiFi.status()),
      WiFi.localIP().toString().c_str());
    Serial.println(msg);

    mblink(5, 50, 50);
    delay(500);
  }

  sprintf(msg, "WiFi connected with IP %s", WiFi.localIP().toString().c_str());
  Serial.println(msg);
}

const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}
