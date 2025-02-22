cmake_minimum_required(VERSION 3.15)
project("Adafruit_SSD1306" LANGUAGES CXX)

set(MCU     atmega328p)
set(F_CPU   16000000UL)
set(BOARD   __AVR_ATmega328__)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -Os -Wall -DF_CPU=${F_CPU} -D${BOARD} -DARDUINO=10607")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -std=c++11 -Os -Wall -DF_CPU=${F_CPU} -D${BOARD} -DARDUINO=10607")



add_library(${PROJECT_NAME} STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Adafruit_SSD1306.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/variants/eightanaloginputs)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/libraries/Adafruit-GFX)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/libraries/Adafruit_BusIO)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/libraries/SPI/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/libraries/Wire/src)