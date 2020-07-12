#!/bin/bash

device="wemos"
pio run -e "$device" && pio run -t upload -e "$device" && pio run -t monitor -e "$device"
