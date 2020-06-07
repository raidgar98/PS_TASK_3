cmake_minimum_required(VERSION 3.10)
project(drag_n_drop_component CXX)

file( GLOB DRAG_N_DROP_FILES drag_n_drop.cpp )

add_library(drag_n_drop STATIC ${DRAG_N_DROP_FILES})

target_link_libraries(drag_n_drop component)
