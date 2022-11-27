// Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
// Use of this source code is governed by the GPL-3.0
// license that can be found in the LICENSE file.

#include <Arduino.h>
#include "led.h"

void blink(int on, int off) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(on);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(off);
}

void blink_multiple(int count, int on, int off) {
  for (int i = 0; i < count; i++) {
    blink(on, off);
  }
}
