cmake_minimum_required(VERSION 3.28)
project(
        neuHem
        DESCRIPTION "neural detection of hemangiomas on a child's body"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

find_package(pybind11 CONFIG REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(lib)