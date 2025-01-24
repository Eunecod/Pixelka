cmake_minimum_required(VERSION 3.15)
project("Pixelka" LANGUAGES C CXX)


add_executable(${PROJECT_NAME}.elf "Pixelka.c")
target_include_directories(${PROJECT_NAME}.elf PUBLIC include)
target_compile_options(${PROJECT_NAME}.elf PRIVATE -finput-charset=UTF-8)

# Генерация .hex файла после сборки .elf
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Создание .hex файла"
)

# Добавление кастомной цели для загрузки на Arduino
add_custom_target(upload ALL
    COMMAND avrdude -c ${AVRDUDE_LOADER} -p ${AVRDUDE_CONTROLER} -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Загрузка прошивки на Arduino"
)
