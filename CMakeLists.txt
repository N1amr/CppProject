cmake_minimum_required(VERSION 3.6)
project(cppProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DLOCAL_PC -DN1AMR")
set(SOURCE_FILES main.cpp)
add_executable(cppProject ${SOURCE_FILES})
