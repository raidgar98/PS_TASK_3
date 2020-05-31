cmake_minimum_required(VERSION 3.10)
project(component_library CXX)

file( GLOB COMPONENT_FILES component.cpp )

add_library(component STATIC ${COMPONENT_FILES})
