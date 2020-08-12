cmake_minimum_required(VERSION 3.16)
project(cpeg C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCE_FILES
        *.c
        )

include_directories(
        include/
        include/internal
)

add_executable(cpeg ${SOURCE_FILES})