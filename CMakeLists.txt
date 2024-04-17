cmake_minimum_required(VERSION 3.28)

project(splan-api LANGUAGES C CXX)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

CHECK_CXX_COMPILER_FLAG("-mtune=generic" COMPILER_SUPPORTS_MTUNE_GENERIC)
if(COMPILER_SUPPORTS_MTUNE_GENERIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=generic")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
