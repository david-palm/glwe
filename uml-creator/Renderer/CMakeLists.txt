cmake_minimum_required(VERSION 3.22)

add_library(Renderer Shader.cpp)
if(EMSCRIPTEN)
    set_target_properties(Renderer PROPERTIES LINK_FLAGS "-s FULL_ES3=1")
else()
    target_link_libraries(Renderer glad)
endif()