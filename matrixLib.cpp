#include <cstddef>
#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix{
public:
    Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), data_(cols * rows){}

    double & operator()(size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    const double & operator()(size_t row, size_t col) const{
        return data_[row * cols_ + col];
    }

    size_t rows() const { return rows_;}
    size_t cols() const { return cols_;}

    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows() || cols_ != other.cols()){
            throw std::invalid_argument("Matrix dimensions need to match for addition");
        }

        Matrix result(rows_,cols_);
        for(size_t i = 0; i < rows_; ++i){
            for(size_t j = 0; j < cols_; ++j){
                result(i,j) = (*this)(i,j) + other(i,j);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if(rows_ != other.rows() || cols_ != other.cols()){
            throw std::invalid_argument("Matrix dimensions need to match for subtracting");
        }

        Matrix result(rows_, cols_);

        for(size_t i = 0; i < rows_; ++i){
            for (size_t j = 0; j < cols_; ++i){
                result(i,j) = (*this)(i,j) - other(i,j);
            }
        }
    }

    
private: 
    size_t rows_, cols_;
    std::vector<double> data_;
};


int main(){
    Matrix A(2,3);

    A(0,0) = 1.0;
    A(0,1) = 2.0;
    A(0,2) = 3.0;
    A(1,0) = 4.0;
    A(1,1) = 5.0;
    A(1,2) = 6.0;
    
    Matrix B(2,3);
    B(0,0) = 1.0;
    B(0,1) = 2.0;
    B(0,2) = 3.0;
    B(1,0) = 4.0;
    B(1,1) = 5.0;
    B(1,2) = 6.0;

    Matrix C = A + B;

    for (size_t i = 0; i < 2; ++i){
        for (size_t j = 0; j < 3; j++){
            std::cout << A(i,j) << (j + 1 < 3 ? ' ' : '\n');
        }
    }

    for (size_t i = 0; i < 2; ++i){
        for (size_t j = 0; j < 3; j++){
            std::cout << C(i,j) << (j + 1 < 3 ? ' ' : '\n');
        }
    }
}


