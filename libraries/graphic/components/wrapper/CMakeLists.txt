cmake_minimum_required(VERSION 3.10)
project(wrapper_component CXX)

file( GLOB WRAPPER_COMPONENT_FILES wrapper.cpp )

add_library(wrapper STATIC ${WRAPPER_COMPONENT_FILES})
