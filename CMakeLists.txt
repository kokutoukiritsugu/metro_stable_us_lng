cmake_minimum_required(VERSION 3.8)
project(metro_stable_us_lng)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
file(COPY string table
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(metro_stable_us_lng ${SOURCE_FILES})
