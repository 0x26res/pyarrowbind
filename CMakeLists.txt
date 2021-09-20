PROJECT(pyarrowbind)
CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)

FIND_PACKAGE(Python3 COMPONENTS Interpreter Development)
FIND_PACKAGE(pybind11 REQUIRED PATHS ${CMAKE_SOURCE_DIR}/venv/lib/python3.8/site-packages/pybind11)


INCLUDE_DIRECTORIES(${pybind11_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/venv/lib/python3.8/site-packages/numpy/core/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/venv/lib/python3.8/site-packages/pyarrow/include)

PROJECT(bindings LANGUAGES CXX)

ADD_LIBRARY(
        bindings
        MODULE
        ${CMAKE_SOURCE_DIR}/bindings.cpp
)

TARGET_LINK_LIBRARIES(
        bindings
        PRIVATE
        pybind11::module
        pybind11::lto
        "${CMAKE_SOURCE_DIR}/venv/lib/python3.8/site-packages/pyarrow/libarrow_python.so"
        "${CMAKE_SOURCE_DIR}/venv/lib/python3.8/site-packages/pyarrow/libarrow.so"
)

# /usr/lib/x86_64-linux-gnu/libarrow.so
pybind11_extension(bindings)
pybind11_strip(bindings)


set_target_properties(
        bindings
        PROPERTIES
        CXX_VISIBILITY_PRESET "hidden"
        CUDA_VISIBILITY_PRESET "hidden")