cmake_minimum_required(VERSION 3.14)
project(
        neuHem
        DESCRIPTION "neural detection of hemangiomas on a child's body"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)
set (PYBIND11_PYTHON_VERSION "3.11")
set(PYTHON_EXECUTABLE "/usr/bin/python3.11")
find_package(OpenCV CONFIG REQUIRED)

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(lib)
#add_subdirectory(src)
add_subdirectory(test)
