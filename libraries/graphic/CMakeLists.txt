cmake_minimum_required(VERSION 3.10)
project(graphic_library CXX)

file( GLOB GRAPHIC_FILES Point.cpp )

add_library(graphic STATIC ${GRAPHIC_FILES})
