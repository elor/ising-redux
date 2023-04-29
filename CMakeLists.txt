cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(CppBootstrap)

include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage("gh:catchorg/Catch2@3.3.2")

add_executable(main main.cpp)
target_link_libraries(main fmt::fmt)

enable_testing()
add_executable(test test.cpp)
target_link_libraries(test Catch2::Catch2 fmt::fmt)

