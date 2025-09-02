#include <cstddef>
#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix{
public:
    Matrix(size_t rows, size_t cols);

    double & operator()(size_t row, size_t col);

    const double & operator()(size_t row, size_t col) const;

    size_t rows() const;
    size_t cols() const;

    Matrix operator+(const Matrix& other) const;

    Matrix operator-(const Matrix& other) const;

    Matrix operator*(const Matrix& other) const;

private: 
    size_t rows_, cols_;
    std::vector<double> data_;
};


// int main(){
//     Matrix A(2,3);

//     A(0,0) = 1.0;
//     A(0,1) = 2.0;
//     A(0,2) = 3.0;
//     A(1,0) = 4.0;
//     A(1,1) = 5.0;
//     A(1,2) = 6.0;
    
//     Matrix B(2,3);
//     B(0,0) = 1.0;
//     B(0,1) = 2.0;
//     B(0,2) = 3.0;
//     B(1,0) = 4.0;
//     B(1,1) = 5.0;
//     B(1,2) = 6.0;

//     Matrix C = A + B;

//     for (size_t i = 0; i < 2; ++i){
//         for (size_t j = 0; j < 3; j++){
//             std::cout << A(i,j) << (j + 1 < 3 ? ' ' : '\n');
//         }
//     }

//     for (size_t i = 0; i < 2; ++i){
//         for (size_t j = 0; j < 3; j++){
//             std::cout << C(i,j) << (j + 1 < 3 ? ' ' : '\n');
//         }
//     }
// }


int main() {
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
