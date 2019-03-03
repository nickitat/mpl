cmake_minimum_required(VERSION 3.2)

add_executable(mpl_tests test.cpp)

target_compile_options(mpl_tests PRIVATE -std=c++17)