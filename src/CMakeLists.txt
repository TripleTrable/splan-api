cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(SRCS_WORKER
    ./main.c
    ./splan/json/getlocs.c
    ./splan/json/locs_parse.c
    ./splan/json/iso_to_utf.c
    ./splan/splan_init.c
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

set_property(TARGET splan-server PROPERTY C_STANDARD 99)
install(TARGETS splan-server DESTINATION ${CMAKE_INSTALL_BINDIR})
target_include_directories(splan-server PRIVATE include)


add_library(splanLib ${SRCS_WORKER})
target_include_directories(splanLib PUBLIC ./include)
