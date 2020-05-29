cmake_minimum_required(VERSION 3.10)

project( PS_TASK_3 )
set(CMAKE_CXX_STANDARD 17)

# Add engine
add_subdirectory(libraries)

# Add tests
add_subdirectory(tests)

# Create Executable
add_executable(main main.cpp)

# OpenGL
find_package(OpenGL REQUIRED COMPONENTS OpenGL )
find_package(GLUT REQUIRED)
include_directories( ${GLUT_INCLUDE_DIRS} )

# Link libraries
add_dependencies(main OpenGL::OpenGL)
target_link_libraries(main OpenGL::OpenGL ${GLUT_LIBRARY} engine graphic)

# Installs
# install(TARGETS main DESTINATION bin)