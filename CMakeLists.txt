cmake_minimum_required(VERSION 3.19)

project(khet LANGUAGES CXX)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# Optimization
#SET(CMAKE_CXX_FLAGS "-pg -no-pie -fno-builtin")
#SET(CMAKE_CXX_FLAGS "-O3")

# Compile with debugging information
set(CMAKE_BUILD_TYPE Debug)

set(PROJ_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(PROJ_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROJ_TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

file(GLOB PROJ_SOURCES
  ${CMAKE_SOURCE_DIR}/include/*.h
  ${CMAKE_SOURCE_DIR}/src/*.cc
)

add_library(khet_lib ${PROJ_SOURCES})
add_executable(khet ${PROJ_SOURCE_DIR}/main.cc)
target_link_libraries(khet khet_lib)

include_directories(${PROJ_INCLUDE_DIR})

# GoogleTest fetching
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# GoogleTest config
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

enable_testing()
include(GoogleTest)

#add_executable(tests ${PROJ_TEST_DIR}/tests.cc)
add_executable(
  tests
  ${PROJ_TEST_DIR}/tests.cc
  ${PROJ_TEST_DIR}/board_tests.cc
  ${PROJ_TEST_DIR}/laser_tests.cc
  ${PROJ_TEST_DIR}/move_tests.cc
  ${PROJ_TEST_DIR}/movegen_tests.cc
  ${PROJ_TEST_DIR}/piece_tests.cc
)

target_link_libraries(
  tests
  gmock
  gtest
  gtest_main
  khet_lib
)

gtest_discover_tests(tests)

