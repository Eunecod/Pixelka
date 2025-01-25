cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C)


add_executable(${PROJECT_NAME}.elf "Pixelka.c")
target_include_directories(${PROJECT_NAME}.elf PUBLIC include)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

add_custom_target(UPLOAD ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_CONTROLER} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)
