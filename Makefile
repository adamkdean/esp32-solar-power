# Copyright (C) 2022 Adam K Dean <adamkdean@googlemail.com>
# Use of this source code is governed by the GPL-3.0
# license that can be found in the LICENSE file.

.PHONY: dev compile monitor upload

#
# Variables
#
SERIAL_PORT ?= /dev/cu.usbserial-0001
FQBN ?= esp32:esp32:nodemcu-32s

#
# Rules
#
dev: upload monitor

compile:
	@echo "Compiling ESP32 firmware"
	@arduino-cli compile --fqbn $(FQBN) firmware

upload: compile
	@echo "Uploading ESP32 firmware"
	@arduino-cli upload -p $(SERIAL_PORT) --fqbn $(FQBN) firmware

monitor:
	@echo "Monitoring ESP32 serial port"
	@screen $(SERIAL_PORT) 115200

