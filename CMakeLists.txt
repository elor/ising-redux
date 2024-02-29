cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Ising)

set(CMAKE_CXX_STANDARD 23)

include(cmake/CPM.cmake)

cpmaddpackage("gh:fmtlib/fmt#10.1.1")
cpmaddpackage("gh:catchorg/Catch2@3.4.0")
cpmaddpackage("gh:pybind/pybind11@2.11.1")

include_directories(include)

add_executable(main src/main.cpp)
target_link_libraries(main fmt::fmt)

enable_testing()
add_executable(test_ising test/test_ising.cpp)
target_link_libraries(test_ising Catch2::Catch2WithMain fmt::fmt)
add_test(NAME test_ising COMMAND test_ising)

pybind11_add_module(pyising src/pyising.cpp)
target_link_libraries(pyising PRIVATE fmt::fmt)
