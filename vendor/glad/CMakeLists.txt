cmake_minimum_required(VERSION 3.22)
project(uml-creator)

add_library(glad src/glad.c)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
