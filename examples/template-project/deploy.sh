#!/bin/bash

BIN=template-project

avr-objcopy -O ihex build/bin/${BIN} ${BIN}.hex
sudo avrdude -cwiring -patmega2560 -P /dev/ttyACM0 -U flash:w:${BIN}.hex -D
