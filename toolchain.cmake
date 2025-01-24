set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER	avr-gcc)


set(MCU		atmega328p)	# ���������������
set(F_CPU	16000000UL)	# ������� ����������

set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# ��������� ��� avrdude (��������� Arduino)
set(AVRDUDE_PORT		"COM5")		# COM-����.
set(AVRDUDE_BAUD		"57600")	# �������� �������� ������.
set(AVRDUDE_CONTROLER	"m328p")	# ��� ����������������.
set(AVRDUDE_LOADER		"arduino")	# ��� ����������.
