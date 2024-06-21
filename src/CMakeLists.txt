cmake_minimum_required(VERSION 3.10)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_C_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(SRCS_WORKER
    ./main.c
    ./splan/request/getlocs.c
    ./splan/request/getpus.c
    ./splan/request/getogs.c
    ./splan/request/getpgsext.c
    ./splan/curl/curl_dl.c
    ./splan/json/locs_parse.c
    ./splan/json/pus_parse.c
    ./splan/json/ogs_parse.c
    ./splan/json/pgsext_parse.c
    ./splan/json/lectures_parse.c
    ./splan/iso_to_utf.c
    ./splan/splan_init.c
    ./splan/data_free.c
    ./rest/default_route.c
    ./db/redis_db.c
    ./sha256_string.c
    )

include(GNUInstallDirs)

add_executable(splan-server ${SRCS_WORKER})

# cJSON
find_package(cJSON REQUIRED)

# CURL
find_package(CURL REQUIRED)

# openssl
find_package(OpenSSL REQUIRED)


include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS})

target_link_libraries(splan-server ${CURL_LIBRARIES})
target_link_libraries(splan-server ${CJSON_LIBRARIES})
target_link_libraries(splan-server ${OPENSSL_LIBRARIES})
target_link_libraries(splan-server ${OPENSSL_SSL_LIBRARY})
target_link_libraries(splan-server ${OPENSSL_CRYPTO_LIBRARY})
target_link_libraries(splan-server hiredis)
target_link_libraries(splan-server microhttpd)
target_link_libraries(splan-server m)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
target_link_libraries(splan-server gcov)
set_target_properties(splan-server PROPERTIES COMPILE_FLAGS "--coverage")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set_property(TARGET splan-server PROPERTY C_STANDARD 11)
install(TARGETS splan-server DESTINATION ${CMAKE_INSTALL_BINDIR})
target_include_directories(splan-server PRIVATE include)

add_library(splanLib ${SRCS_WORKER})
target_compile_definitions(splanLib PUBLIC CURL_GTEST)
set_target_properties(splanLib PROPERTIES COMPILE_FLAGS "--coverage")
target_include_directories(splanLib PUBLIC ./include)
