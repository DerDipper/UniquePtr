cmake_minimum_required(VERSION 3.10)

project(UniquePtr)

include_directories(
    inc/
)

aux_source_directory(test/ TEST)

add_executable(${CMAKE_PROJECT_NAME} ${TEST})

