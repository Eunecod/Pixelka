cmake_minimum_required(VERSION 3.15)
project("Adafruit_SSD1306" LANGUAGES CXX)


file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
add_library(${PROJECT_NAME} STATIC ${SOURCE})