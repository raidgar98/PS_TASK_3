cmake_minimum_required(VERSION 3.10)

project( PS_TASK_3 )
set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL )
find_package(GLUT REQUIRED)

add_dependencies(main OpenGL::OpenGL)
include_directories( ${GLUT_INCLUDE_DIRS} )

target_link_libraries(main OpenGL::OpenGL ${GLUT_LIBRARY} )
