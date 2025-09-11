# MatrixLib

MatrixLib is a simple C++ library for performing basic matrix operations such as addition, subtraction, and multiplication.

## How to Run
1. **Build the Project**:
   - Navigate to the project directory and create a build directory:
     ```bash
     mkdir build && cd build
     ```
   - Run CMake to configure the project:
     ```bash
     cmake ..
     ```
   - Build the project using make:
     ```bash
     make
     ```
2. **Run the Executable**:
   - Execute the compiled program:
     ```bash
     ./MatrixLib
     ```

## File Overview
- **matrixLib.cpp**: Contains the main function demonstrating the usage of the Matrix class.
- **src/Matrix.cpp**: Implements the Matrix class methods.
- **src/Matrix.h**: Declares the Matrix class and its interface.
- **CMakeLists.txt**: Configuration file for building the project with CMake.
- **README.md**: Provides an overview and instructions for the project.

## TODO

- Implement compound assignment operators (+=, -=, *=) for the Matrix class.
