cmake_minimum_required(VERSION 3.10)

project(MatrixLib)

add_executable(MatrixLib src/Matrix.cpp matrixLib.cpp)

target_include_directories(MatrixLib PUBLIC "${PROJECT_SOURCE_DIR}/src")
