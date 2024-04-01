cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(SRCS_WORKER
    ./main.c
    ./splan/request/getlocs.c
    ./splan/request/getpus.c
    ./splan/curl/curl_dl.c
    ./splan/json/locs_parse.c
    ./splan/json/pus_parse.c
    ./splan/iso_to_utf.c
    ./splan/splan_init.c
    ./splan/data_free.c
    )

include(GNUInstallDirs)

add_executable(splan-server ${SRCS_WORKER})

# cJSON
find_package(cJSON REQUIRED)

# CURL
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIRS})

target_link_libraries(splan-server ${CURL_LIBRARIES})
target_link_libraries(splan-server ${CJSON_LIBRARIES})
target_link_libraries(splan-server m)

set_property(TARGET splan-server PROPERTY C_STANDARD 11)
install(TARGETS splan-server DESTINATION ${CMAKE_INSTALL_BINDIR})
target_include_directories(splan-server PRIVATE include)

add_library(splanLib ${SRCS_WORKER})
target_compile_definitions(splanLib PUBLIC CURL_GTEST)
set_target_properties(splanLib PROPERTIES COMPILE_FLAGS "--coverage")
target_include_directories(splanLib PUBLIC ./include)
