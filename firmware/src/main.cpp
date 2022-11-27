// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "lib/led/led.h"
#include "lib/wifi/wifi.h"
#include "main.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  blink_multiple(10, 100, 100);
  connect_to_wifi();
}

void loop() {
  char msg[64];
  sprintf(msg, "%s %s",
    wl_status_to_string(WiFi.status()),
    WiFi.localIP().toString().c_str());
  Serial.println(msg);
  blink(100, 400);
}
