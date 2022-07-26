cmake_minimum_required(VERSION 3.0)

project(app)

option (FLTK_BUILD_TEST     "Build test/demo programs" OFF)

add_subdirectory(source/libraries/fltk)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/source/libraries/fltk fltk)

add_executable(my_execut main.cpp)

target_link_libraries(my_execut fltk)