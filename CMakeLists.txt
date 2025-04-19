cmake_minimum_required(VERSION 3.15)
include(cmake/avr-toolchain.cmake)

project(Pixelka C CXX ASM)


add_executable(${PROJECT_NAME}.elf Pixelka.cpp)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-size $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Размер firmware:"
)
