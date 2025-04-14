cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX ASM)

include(cmake/avr-gcc-toolchain.cmake)


add_executable(${PROJECT_NAME}.elf "Pixelka.cpp")