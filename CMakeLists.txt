cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(target_sources_directories target directories)
    file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/${directories}/*.cpp")
    target_sources(${target} PRIVATE ${files})
endfunction()

set(AVR_DEFINITIONS
    "__AVR_ATmega328__"
    "F_CPU=16000000UL"
)




add_executable(${PROJECT_NAME}.elf "Pixelka.cpp")
target_sources_directories(${PROJECT_NAME}.elf "core/cores/arduino")

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/cores/arduino)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/avr-core)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_CONTROLER} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC ${AVR_DEFINITIONS})
