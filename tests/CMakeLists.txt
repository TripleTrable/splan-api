
set(CMAKE_C_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
include(CTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


# cJSON
find_package(cJSON REQUIRED)

# CURL
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIRS})




add_executable(splan_init_test ./splan_init.cpp)
target_link_libraries(splan_init_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)
add_test(splan_init_gtest splan_init_test)


add_executable(getlocs_test ./getlocks.cpp)
target_link_libraries(getlocs_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(getlocs_test PUBLIC CURL_GTEST)
add_test(getlocs_gtest getlocs_test)


add_executable(iso8859_to_utf_test ./iso8859_to_utf_test.cpp)
configure_file(./iso8859_test.txt ./ COPYONLY)
configure_file(./utf_8_test.txt ./ COPYONLY)

target_link_libraries(iso8859_to_utf_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(iso8859_to_utf_test PUBLIC CURL_GTEST)
add_test(iso8859_to_utf_gtest iso8859_to_utf_test)

add_executable(locs_parse_test ./locs_parse.cpp)
target_link_libraries(locs_parse_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(locs_parse_test PUBLIC CURL_GTEST)
configure_file(./curl_getlocs_raw.txt ./ COPYONLY)
add_test(locs_parse_gtest locs_parse_test)


add_executable(curl_get_test ./curl_dl.cpp)
target_link_libraries(curl_get_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(curl_get_test PUBLIC CURL_GTEST)
configure_file(./curl_getlocs_raw.txt ./ COPYONLY)
add_test(curl_get_gtest curl_get_test)


add_executable(getpus_test ./getpus.cpp)
target_link_libraries(getpus_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(getpus_test PUBLIC CURL_GTEST)
configure_file(./curl_getpus_raw.txt ./ COPYONLY)
add_test(getpus_gtest getpus_test)


add_executable(pus_parse_test ./pus_parse.cpp)
target_link_libraries(pus_parse_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(pus_parse_test PUBLIC CURL_GTEST)
configure_file(./curl_getpus_raw.txt ./ COPYONLY)
add_test(pus_parse_gtest pus_parse_test)

add_executable(rest_default_route_test ./rest_default_route.cpp)
target_link_libraries(rest_default_route_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        hiredis
        microhttpd
        m)

add_test(rest_default_route_gtest rest_default_route_test)

add_executable(getogs_test ./getogs.cpp)
target_link_libraries(getogs_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(getogs_test PUBLIC CURL_GTEST)
configure_file(./curl_getogs_raw.txt ./ COPYONLY)
add_test(getogs_gtest getogs_test)

add_executable(ogs_parse_test ./ogs_parse.cpp)
target_link_libraries(ogs_parse_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(ogs_parse_test PUBLIC CURL_GTEST)
add_test(ogs_parse_gtest ogs_parse_test)

add_executable(getpgsext_test ./getpgsext.cpp)
target_link_libraries(getpgsext_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(getpgsext_test PUBLIC CURL_GTEST)
configure_file(./curl_getpgsext_raw.txt ./ COPYONLY)
add_test(getpgsext_gtest getpgsext_test)

add_executable(pgsext_parse_test ./pgsext_parse.cpp)
target_link_libraries(pgsext_parse_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(pgsext_parse_test PUBLIC CURL_GTEST)
add_test(pgsext_parse_gtest pgsext_parse_test)

add_executable(lectures_parse_test ./lectures_parse.cpp)
target_link_libraries(lectures_parse_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

target_compile_definitions(lectures_parse_test PUBLIC CURL_GTEST)
add_test(lectures_parse_gtest lectures_parse_test)

# THIS TEST CAN ONLY BE RUN LOCALY, SOMEHOW THE PIPELIN CAUSES SEGFAULTS WHICH
# CANNOT BE DEBUGGED
#add_executable(data_free_test ./data_free.cpp)
#target_link_libraries(data_free_test
#    PRIVATE
#        GTest::GTest
#        splanLib
#        ${CURL_LIBRARIES}
#        ${CJSON_LIBRARIES}
#        ${OPENSSL_SSL_LIBRARY}
#        ${OPENSSL_CRYPTO_LIBRARY}
#        hiredis
#        microhttpd
#        m)
#
#target_compile_definitions(data_free_test PUBLIC CURL_GTEST)
#add_test(data_free_gtest data_free_test)

add_executable(redis_db_init ./redis_init.cpp)
target_link_libraries(redis_db_init
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        hiredis
        microhttpd
        m)

target_compile_definitions(redis_db_init PUBLIC CURL_GTEST)
add_test(redis_db_gtest redis_db_init)

add_executable(redis_store_lookup_test ./redis_store_lookup.cpp)
target_link_libraries(redis_store_lookup_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        hiredis
        microhttpd
        m)

target_compile_definitions(redis_store_lookup_test PUBLIC CURL_GTEST)
add_test(redis_store_lookup_gtest redis_store_lookup_test)
