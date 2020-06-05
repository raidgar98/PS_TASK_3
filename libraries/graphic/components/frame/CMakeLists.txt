cmake_minimum_required(VERSION 3.10)
project(frame_componen CXX)

file( GLOB FRAME_COMPONENT_FILES frame.cpp )

add_library(frame STATIC ${FRAME_COMPONENT_FILES})
