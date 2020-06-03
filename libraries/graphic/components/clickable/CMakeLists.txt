cmake_minimum_required(VERSION 3.10)
project(clickable_component CXX)

file( GLOB CLICKABLE_FILES clickable.cpp )

add_library(clickable STATIC ${CLICKABLE_FILES})

target_link_libraries(clickable component)
