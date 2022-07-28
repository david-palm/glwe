cmake_minimum_required(VERSION 3.22)
project(uml-creator)
add_executable(uml-creator uml-creator/main.cpp uml-creator/Platform/OpenGL/OpenGLBuffer.h uml-creator/Platform/OpenGL/OpenGLBuffer.cpp)
set(CMAKE_CXX_STANDARD 23)

# Adding subdirectory for uml creator
add_subdirectory(uml-creator)


if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(uml-creator PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1")
else()
    # Adding subdirectories for vendor libraries
    add_subdirectory(vendor/glfw)
    add_subdirectory(vendor/glad)

    # Linking libraries to main uml-creator project
    target_link_libraries(uml-creator glfw)
    target_link_libraries(uml-creator glad)

    # Adding include directories of libraries to main uml-creator project
    target_include_directories(uml-creator PUBLIC /vendor/glfw/include)
    target_include_directories(uml-creator PUBLIC /vendor/glad/include)
endif()