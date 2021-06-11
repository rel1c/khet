cmake_minimum_required(VERSION 3.19)

project(khet LANGUAGES CXX)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

set(PROJ_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(PROJ_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROJ_TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

file(GLOB PROJ_SOURCES
  ${CMAKE_SOURCE_DIR}/include/*.h
  ${CMAKE_SOURCE_DIR}/src/*.cc
)

add_executable(khet ${PROJ_SOURCES})

include_directories(${PROJ_INCLUDE_DIR})

# GoogleTest fetching
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# GoogleTest config
enable_testing()

add_executable(tests ${PROJ_TEST_DIR}/tests.cc)

target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

