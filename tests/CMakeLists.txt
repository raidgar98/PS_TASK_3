cmake_minimum_required(VERSION 3.10)
project(engine_tests)

enable_testing()

set(Boost_ADDITIONAL_VERSIONS "1.65" "1.65.0")

find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)

add_executable(engine_tests SwitcherEngineTest.cpp)
target_include_directories(engine_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(engine_tests PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(engine_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} engine)

add_test(NAME engine_tests COMMAND engine_tests)
