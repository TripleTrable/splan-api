
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
