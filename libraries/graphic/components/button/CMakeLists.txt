cmake_minimum_required(VERSION 3.10)
project(button_component CXX)

file( GLOB BUTTON_FILES button.cpp )

add_library(button STATIC ${BUTTON_FILES})

target_link_libraries(button rectangle_component clickable)
