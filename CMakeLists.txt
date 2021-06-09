cmake_minimum_required(VERSION 3.19)

project(khet LANGUAGES CXX)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

set(PROJ_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(PROJ_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(khet ${PROJ_SOURCE_DIR}/main.cc)

include_directories(${PROJ_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)
