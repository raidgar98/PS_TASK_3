cmake_minimum_required(VERSION 3.10)
project(utility_library CXX)

file( GLOB UTILITY_FILES 
    Property.cpp 
)

add_library(utility STATIC ${GRAPHIC_FILES})
