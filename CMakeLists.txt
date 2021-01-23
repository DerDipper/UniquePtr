cmake_minimum_required(VERSION 3.10)

project(UniquePtr)
enable_testing()

include_directories(
    inc/
)

aux_source_directory(test/ TEST)

add_executable(${CMAKE_PROJECT_NAME}_Test ${TEST})

add_test(NAME UniquePtr COMMAND ${CMAKE_PROJECT_NAME}_Test)

