cmake_minimum_required(VERSION 3.10)
project(rectangle_component_library CXX)

file( GLOB RECTANGLE_COMPONENT_FILES rectangle_component.cpp )

add_library(rectangle_component STATIC ${RECTANGLE_COMPONENT_FILES})
