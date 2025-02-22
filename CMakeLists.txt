cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX ASM)

function(target_sources_directories TARGET DIRECTORIES EXTENSIONS)
    file(GLOB_RECURSE files "${DIRECTORIES}/${EXTENSIONS}")
    target_sources(${TARGET} PRIVATE ${files})
endfunction()

set(MCU     atmega328p)
set(F_CPU   16000000UL)
set(BOARD   __AVR_ATmega328__)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -Os -Wall -DF_CPU=${F_CPU} -D${BOARD}")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -Os -Wall -DF_CPU=${F_CPU} -D${BOARD}")

set(ARDUINO_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino")



add_executable(${PROJECT_NAME}.elf "Pixelka.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "main.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.S")

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/variants/eightanaloginputs)

target_link_libraries(${PROJECT_NAME}.elf -lm -lc)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

set(AVRDUDE_LOADER  arduino)
set(AVRDUDE_PORT    COM6)
set(AVRDUDE_BAUD    57600)
set(AVRDUDE_MCU     ${MCU})

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_CONTROLER} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -v -V -D -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)
