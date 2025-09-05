#include <cstddef>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include "src/Matrix.h"

void benchmark() {
    const size_t size = 1000; // Increased size for large matrices
    Matrix A(size, size);
    Matrix B(size, size);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            A(i, j) = static_cast<double>(i + j);
            B(i, j) = static_cast<double>(i - j);
        }
    }

    // Benchmark normal multiplication
    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = A * B;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Normal multiplication took " << duration.count() << " seconds." << std::endl;

    // Benchmark threaded multiplication
    size_t default_threads = std::thread::hardware_concurrency();
    start = std::chrono::high_resolution_clock::now();
    Matrix D = A.parallelMultiply(B, default_threads);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Threaded multiplication with " << default_threads << " threads took " << duration.count() << " seconds." << std::endl;

    // Vary the number of threads
    size_t max_threads = std::thread::hardware_concurrency();
    for (size_t num_threads = 1; num_threads <= max_threads; ++num_threads) {
        std::cout << "Testing with " << num_threads << " threads." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        Matrix E = A.parallelMultiply(B, num_threads);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Multiplication with " << num_threads << " threads took " << duration.count() << " seconds." << std::endl;
    }
}

int main() {
    benchmark();
    // Test 1: Addition
    Matrix A(2,3);
    A(0,0)=1; A(0,1)=2; A(0,2)=3;
    A(1,0)=4; A(1,1)=5; A(1,2)=6;

    Matrix B(2,3);
    B(0,0)=7; B(0,1)=8; B(0,2)=9;
    B(1,0)=10; B(1,1)=11; B(1,2)=12;

    Matrix C = A + B; 
    std::cout << "Test 1 (Addition):" << std::endl;
    for (size_t i=0;i<C.rows();++i){
        for (size_t j=0;j<C.cols();++j){
            std::cout << C(i,j) << " ";
        }
        std::cout << std::endl;
    }
    // Expected: [8 10 12; 14 16 18]

    // Test 2: Subtraction
    Matrix D = B - A;
    std::cout << "\nTest 2 (Subtraction):" << std::endl;
    for (size_t i=0;i<D.rows();++i){
        for (size_t j=0;j<D.cols();++j){
            std::cout << D(i,j) << " ";
        }
        std::cout << std::endl;
    }
    // Expected: [6 6 6; 6 6 6]

    // Test 3: Multiplication (2x3) * (3x2) = (2x2)
    Matrix E(3,2);
    E(0,0)=1; E(0,1)=2;
    E(1,0)=3; E(1,1)=4;
    E(2,0)=5; E(2,1)=6;

    Matrix F = A * E;
    std::cout << "\nTest 3 (Multiplication):" << std::endl;
    for (size_t i=0;i<F.rows();++i){
        for (size_t j=0;j<F.cols();++j){
            std::cout << F(i,j) << " ";
        }
        std::cout << std::endl;
    }
    // Expected result:
    // Row 0: [1*1 + 2*3 + 3*5 , 1*2 + 2*4 + 3*6] = [22, 28]
    // Row 1: [4*1 + 5*3 + 6*5 , 4*2 + 5*4 + 6*6] = [49, 64]

    // Test 4: Invalid Addition (different dimensions)
    try {
        Matrix G(3,3);
        Matrix H = A + G; // should throw
    } catch (const std::invalid_argument& e) {
        std::cout << "\nTest 4 (Invalid Addition caught): " << e.what() << std::endl;
    }

    // Test 5: Invalid Multiplication (cols != rows)
    try {
        Matrix I(2,2);
        Matrix J = A * I; // A(2x3) * I(2x2) → invalid
    } catch (const std::invalid_argument& e) {
        std::cout << "Test 5 (Invalid Multiplication caught): " << e.what() << std::endl;
    }
}
