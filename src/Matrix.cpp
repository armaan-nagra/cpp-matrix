#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols)
: rows_(rows), cols_(cols), data_(cols * rows){}


double & Matrix::operator()(size_t row, size_t col) {
    return data_[row * cols_ + col];
}

const double & Matrix::operator()(size_t row, size_t col) const{
    return data_[row * cols_ + col];
}

size_t Matrix::rows() const { return rows_;}
size_t Matrix::cols() const { return cols_;}

Matrix Matrix::operator+(const Matrix& other) const {
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

Matrix Matrix::operator-(const Matrix& other) const {
    if(rows_ != other.rows() || cols_ != other.cols()){
        throw std::invalid_argument("Matrix dimensions need to match for subtracting");
    }

    Matrix result(rows_, cols_);

    for(size_t i = 0; i < rows_; ++i){
        for (size_t j = 0; j < cols_; ++j){
            result(i,j) = (*this)(i,j) - other(i,j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows()){
        throw std::invalid_argument("Matrix dimensions do not allow for multiplication");
    }
    
    Matrix result(rows_, other.cols());
    for (size_t i = 0; i < rows_; ++i){
        for (size_t j = 0; j < other.cols(); ++j){
            double total = 0.0;
            for(size_t k = 0; k < cols_; ++k){
                total += (*this)(i,k) * other(k,j);
            }
            result(i,j) = total;
        }
    }
    return result;
}
