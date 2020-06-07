cmake_minimum_required(VERSION 3.10)
project(graphic_library CXX)

add_subdirectory( components )

file( GLOB GRAPHIC_FILES 
    Point.cpp
    Dimension.cpp
)

add_library(graphic STATIC ${GRAPHIC_FILES})
