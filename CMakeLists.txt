cmake_minimum_required(VERSION 3.12)
project(CppBootstrap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main main.cpp)
target_link_libraries(main ${CONAN_LIBS})

enable_testing()

add_executable(my_test test.cpp)
target_link_libraries(my_test ${CONAN_LIBS})
add_test(NAME my_test COMMAND my_test)

