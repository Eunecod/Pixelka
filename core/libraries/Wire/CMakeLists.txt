cmake_minimum_required(VERSION 3.15)
project("Wire" LANGUAGES CXX)


file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/utility/*.c")
add_library(${PROJECT_NAME} STATIC ${SOURCE})