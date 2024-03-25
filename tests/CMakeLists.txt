
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

add_executable(splan_init_test ./splan_init.cpp)

# cJSON
find_package(cJSON REQUIRED)

# CURL
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIRS})




target_link_libraries(splan_init_test
    PRIVATE
        GTest::GTest
        splanLib
        ${CURL_LIBRARIES}
        ${CJSON_LIBRARIES}
        m)

add_test(splan_init_gtest splan_init_test)
