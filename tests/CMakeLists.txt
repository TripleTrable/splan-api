cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(SRCS_WORKER
    ./src/main.c
    ./src/splan/json/getlocs.c
    ./src/splan/json/locs_parse.c
    ./src/splan/json/iso_to_utf.c
    ./src/splan/splan_init.c
    )

include(GNUInstallDirs)

add_executable(splan-server ${SRCS_WORKER})
find_package(cJSON REQUIRED)
message(STATUS ${CJSON_INCLUDE_DIRS})
message(STATUS ${CJSON_LIBRARIES})

# CURL
find_package(CURL REQUIRED)


include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIRS})


target_link_libraries(splan-server ${CURL_LIBRARIES})
target_link_libraries(splan-server ${CJSON_LIBRARIES})
target_link_libraries(splan-server m)

add_subdirectory(TARGETS splan-server DESTINATION ${CMAKE_INSTALL_BINDIR})
