cmake_minimum_required(VERSION 3.15)
project("SPI" LANGUAGES CXX)


file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${SOURCE})