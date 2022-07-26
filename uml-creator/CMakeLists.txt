cmake_minimum_required(VERSION 3.22)

add_executable(uml-creator main.cpp)

add_subdirectory(Math)

target_link_libraries(uml-creator Math)