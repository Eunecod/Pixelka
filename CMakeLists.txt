cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX ASM)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core")

function(target_sources_directories TARGET DIRECTORIES EXTENSIONS)
    file(GLOB_RECURSE files "${DIRECTORIES}/${EXTENSIONS}")
    target_sources(${TARGET} PRIVATE ${files})
endfunction()

set(MCU     atmega328p)
set(F_CPU   16000000UL)
set(BOARD   __AVR_ATmega328__)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -Os -flto -Wall -DF_CPU=${F_CPU} -D${BOARD} -DARDUINO=10607")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -Os -flto -Wall -DF_CPU=${F_CPU} -D${BOARD} -DARDUINO=10607")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARDUINO_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino")



add_executable(${PROJECT_NAME}.elf "Pixelka.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.S")

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/variants/eightanaloginputs)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/SoftwareSerial/src)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/Adafruit_SSD1306)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/Adafruit-GFX)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/Adafruit-GFX/Fonts)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/Adafruit_BusIO)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/SPI/src)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/libraries/Wire/src)

target_link_libraries(${PROJECT_NAME}.elf -lm -lc)
target_link_libraries(${PROJECT_NAME}.elf SoftwareSerial)
target_link_libraries(${PROJECT_NAME}.elf Adafruit_SSD1306)
target_link_libraries(${PROJECT_NAME}.elf Adafruit-GFX)
target_link_libraries(${PROJECT_NAME}.elf Adafruit_BusIO)
target_link_libraries(${PROJECT_NAME}.elf SPI)
target_link_libraries(${PROJECT_NAME}.elf Wire)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

set(AVRDUDE_LOADER  arduino)
set(AVRDUDE_PORT    COM6)
set(AVRDUDE_BAUD    57600)
set(AVRDUDE_MCU     ${MCU})

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_MCU} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -v -V -D -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)
