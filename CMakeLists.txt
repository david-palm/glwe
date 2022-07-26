cmake_minimum_required(VERSION 3.22)
project(uml-creator)

set(CMAKE_CXX_STANDARD 23)

add_executable(uml-creator main.cpp)

# Adding subdirectories for libraries
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

# Linking libraries to main uml-creator project
target_link_libraries(uml-creator glfw)
target_link_libraries(uml-creator glad)

# Adding include directories of libraries to main uml-creator project
target_include_directories(uml-creator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
target_include_directories(uml-creator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
