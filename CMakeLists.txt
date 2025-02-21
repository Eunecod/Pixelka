cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX ASM)

function(target_sources_directories TARGET DIRECTORIES EXTENSIONS)
    file(GLOB_RECURSE files "${DIRECTORIES}/${EXTENSIONS}")
    target_sources(${TARGET} PRIVATE ${files})
endfunction()

set(AVR_DEFINITIONS
    "__AVR_ATmega328__"
    "mmcu=atmega328p"
    "F_CPU=16000000UL"
)

set(ARDUINO_CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino")


add_executable(${PROJECT_NAME}.elf "Pixelka.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "main.cpp")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.c")
target_sources_directories(${PROJECT_NAME}.elf ${ARDUINO_CORE_PATH} "*.S")

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/variants/standard)

target_link_libraries(${PROJECT_NAME}.elf -lm -lc)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -v -p ${AVRDUDE_CONTROLER} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC ${AVR_DEFINITIONS})