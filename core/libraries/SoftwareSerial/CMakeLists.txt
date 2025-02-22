cmake_minimum_required(VERSION 3.15)
project("SoftwareSerial" LANGUAGES CXX)

set(MCU     atmega328p)
set(F_CPU   16000000UL)
set(BOARD   __AVR_ATmega328__)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -Os -Wall -DF_CPU=${F_CPU} -D${BOARD}")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -Os -Wall -DF_CPU=${F_CPU} -D${BOARD}")



add_library(${PROJECT_NAME} STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/SoftwareSerial.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/core/variants/eightanaloginputs)