cmake_minimum_required(VERSION 3.15)
project("Adafruit-GFX" LANGUAGES CXX)


file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
add_library(${PROJECT_NAME} STATIC ${SOURCE})