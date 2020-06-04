cmake_minimum_required(VERSION 3.10)
project(window_component CXX)

file( GLOB WINDOW_FILES window.cpp )

add_library(window STATIC ${WINDOW_FILES})

find_package(OpenGL REQUIRED COMPONENTS OpenGL )
find_package(GLUT REQUIRED)
include_directories( ${GLUT_INCLUDE_DIRS} )

# Link libraries
add_dependencies(window OpenGL::OpenGL)
target_link_libraries(window rectangle_component button OpenGL::OpenGL ${GLUT_LIBRARY} pthread sneaky_pointer )
