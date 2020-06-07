cmake_minimum_required(VERSION 3.10)
project(lbutton_component CXX)

file( GLOB LBUTTON_FILES lbutton.cpp )

add_library(lbutton STATIC ${LBUTTON_FILES})

target_link_libraries(lbutton button label)
