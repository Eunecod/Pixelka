# cmake/avr-gcc-toolchain.cmake

set(CMAKE_SYSTEM_NAME   Arduino)

set(CMAKE_ASM_COMPILER  /usr/bin/avr-gcc)
set(CMAKE_C_COMPILER    /usr/bin/avr-gcc)
set(CMAKE_CXX_COMPILER  /usr/bin/avr-g++)