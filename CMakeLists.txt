cmake_minimum_required(VERSION 3.19)

project(khet LANGUAGES CXX)

SET(PROJ_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
SET(PROJ_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

add_executable(khet ${PROJ_SOURCE_DIR}/main.cc)

INCLUDE_DIRECTORIES(${PROJ_INCLUDE_DIR})
