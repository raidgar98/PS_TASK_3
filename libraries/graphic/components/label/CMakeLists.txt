cmake_minimum_required(VERSION 3.10)
project(label_component CXX)

file( GLOB LABEL_FILES label.cpp )

add_library(label STATIC ${LABEL_FILES})

target_link_libraries(label rectangle_component frame)
