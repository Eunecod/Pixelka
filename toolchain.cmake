set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER	avr-gcc)


set(MCU		atmega328p)	# Микроконтроллер
set(F_CPU	16000000UL)	# Частота процессора

set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# Настройки для avrdude (загрузчик Arduino)
set(AVRDUDE_PORT		"COM5")		# COM-порт.
set(AVRDUDE_BAUD		"57600")	# Скорость передачи данных.
set(AVRDUDE_CONTROLER	"m328p")	# Тип микроконтроллера.
set(AVRDUDE_LOADER		"arduino")	# Тип загрузчика.
