# For a list of all variables that can be overridden, see:
# 	https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md

BOARD_TAG = mega
BOARD_SUB = atmega2560
MONITOR_PORT = /dev/cu.usbmodem14211
MONITOR_BAUDRATE = 9600

ARDUINO_DIR = $(HOME)/Applications/Arduino.app/Contents/Java
ARDMK_DIR = $(realpath ../../libraries/Arduino-Makefile)

# ARDUINO_LIBS = MemoryFree Plantokei-Music SPI Adafruit-GFX-Library Adafruit-ST7735-Library
USER_LIB_PATH =  $(realpath ../../libraries)

AVR_TOOLS_DIR = /usr/local
AVRDUDE = /usr/local/bin/avrdude

CFLAGS_STD = -std=gnu11
CXXFLAGS_STD = -std=gnu++11
CXXFLAGS = -pedantic -Wall -Wextra

OBJDIR = $(realpath ./build)

include $(ARDMK_DIR)/Arduino.mk
