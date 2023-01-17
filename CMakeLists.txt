cmake_minimum_required(VERSION 3.22)
project(glwe)
add_executable(glwe
        glwe/Platform/OpenGL/OpenGLBuffer.h
        glwe/Platform/OpenGL/OpenGLBuffer.cpp
        glwe/Platform/OpenGL/OpenGLVertexArray.cpp
        glwe/Platform/OpenGL/OpenGLVertexArray.h
        glwe/main.cpp
        glwe/Application.cpp
        glwe/Events/Event.h
        glwe/Events/KeyEvent.h
        glwe/Window.h
        glwe/Platform/Windows/WindowsWindow.h
        glwe/Platform/Windows/WindowsWindow.cpp
        glwe/Events/WindowEvent.h
        glwe/Events/MouseEvent.h
        glwe/Layer.h
        glwe/Layer.cpp
        glwe/LayerStack.h
        glwe/LayerStack.cpp)
set(CMAKE_CXX_STANDARD 23)

# Adding subdirectory for glwe
add_subdirectory(glwe)


if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(glwe PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1")
else()
    # Adding subdirectories for vendor libraries
    add_subdirectory(vendor/glfw)
    add_subdirectory(vendor/glad)
    add_subdirectory(vendor/imgui)

    # Linking libraries to main glwe project
    target_link_libraries(glwe glfw)
    target_link_libraries(glwe glad)
    target_link_libraries(glwe imgui)

    # Adding include directories of libraries to main glwe project
    target_include_directories(glwe PUBLIC /vendor/glfw/include)
    target_include_directories(glwe PUBLIC /vendor/glad/include)
    target_include_directories(glwe PUBLIC /vendor/imgui)
endif()