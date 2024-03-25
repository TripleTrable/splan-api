cmake_minimum_required(VERSION 3.28)

project(splan-api LANGUAGES C CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS true)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
