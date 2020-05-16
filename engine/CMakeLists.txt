cmake_minimum_required(VERSION 3.10)
project(engine_library)

file( GLOB ENGINE_FILES SwitcherEngine.cpp )# coordinates.hpp SwitcherEngine.hpp )

add_library(engine STATIC ${ENGINE_FILES})

# install(TARGETS engine DESTINATION lib)
# install(FILES ${ENGINE_FILES} DESTINATION include)