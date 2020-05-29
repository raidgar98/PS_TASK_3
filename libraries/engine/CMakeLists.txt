cmake_minimum_required(VERSION 3.10)
project(engine_library)

file( GLOB ENGINE_FILES SwitcherEngine.cpp )

add_library(engine STATIC ${ENGINE_FILES})

option( UNIX "build for unix" ON )

# Additional definitions
if(${UNIX})
	target_compile_definitions( engine PRIVATE UNIX=1 )
else()
	target_compile_definitions( engine PRIVATE UNIX=0 )
endif(${UNIX})

# install(TARGETS engine DESTINATION lib)
# install(FILES ${ENGINE_FILES} DESTINATION include)