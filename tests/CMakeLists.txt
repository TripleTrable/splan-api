
set(CMAKE_C_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

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
