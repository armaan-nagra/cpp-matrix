cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MatrixLib)

# Add the executable
add_executable(MatrixLib src/Matrix.cpp)

target_include_directories(MatrixLib PUBLIC "${PROJECT_SOURCE_DIR}/src")
