cmake_minimum_required(VERSION 3.22)

add_subdirectory(Math)
add_subdirectory(Renderer)

target_link_libraries(uml-creator Math Renderer)