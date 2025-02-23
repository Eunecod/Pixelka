cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX ASM)

function(target_sources_directories TARGET DIRECTORIES EXTENSIONS)
    file(GLOB_RECURSE files "${DIRECTORIES}/${EXTENSIONS}")
    target_sources(${TARGET} PRIVATE ${files})
endfunction()

set(MCU     atmega328p)
set(F_CPU   16000000UL)
set(BOARD   __AVR_ATmega328__)

set(CMAKE_C_FLAGS   "-mmcu=${MCU} -w -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-threadsafe-statics -DF_CPU=${F_CPU} -D${BOARD} -DARDUINO=10607")
set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-mmcu=${MCU} -Wl,--gc-sections -Wl,--relax -flto")

set(ARDUINO_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino")
set(ARDUINO_VARIANT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/variants/eightanaloginputs")
set(ARDUINO_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/libraries")
set(ARDUINO_ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")




add_executable(${PROJECT_NAME}.elf "Pixelka.cpp")
target_sources_directories(${PROJECT_NAME}.elf "${CMAKE_CURRENT_SOURCE_DIR}/src" "*.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.S")

include_directories(${ARDUINO_CORE_PATH} ${ARDUINO_VARIANT_PATH} ${ARDUINO_ASSETS_PATH} ${ARDUINO_LIBRARY_PATH}/SoftwareSerial/src 
    ${ARDUINO_LIBRARY_PATH}/Adafruit_SSD1306 ${ARDUINO_LIBRARY_PATH}/Adafruit-GFX ${ARDUINO_LIBRARY_PATH}/Adafruit-GFX/Fonts
    ${ARDUINO_LIBRARY_PATH}/Adafruit_BusIO ${ARDUINO_LIBRARY_PATH}/SPI/src ${ARDUINO_LIBRARY_PATH}/Wire/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}.elf -lm -lc SoftwareSerial Adafruit_SSD1306 Adafruit-GFX Adafruit_BusIO SPI Wire)
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC UBRRH __AVR__)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

set(AVRDUDE_LOADER  arduino)
set(AVRDUDE_PORT    COM6)
set(AVRDUDE_BAUD    57600)
set(AVRDUDE_MCU     ${MCU})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-size --format=sysv $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Информация о размере программы"
)

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_MCU} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -v -V -D -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)

add_subdirectory(${ARDUINO_LIBRARY_PATH})