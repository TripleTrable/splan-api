cmake_minimum_required(VERSION 3.10)

project(splan-api)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(SRCS_WORKER
    src/main.c
    )

include(GNUInstallDirs)

add_executable(splan-server ${SRCS_WORKER})
target_link_libraries(splan-server m)

install(TARGETS splan-server DESTINATION ${CMAKE_INSTALL_BINDIR})
