#!/usr/bin/env sh
FIRMWARE="$1"
avrdude -c usbasp -p t1634 -Uflash:w:"$FIRMWARE"
