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

Matrix Matrix::parallelMultiply(const Matrix& other, size_t num_threads) const {
    if (cols_ != other.rows()){
        throw std::invalid_argument("Matrix dimensions do not allow for multiplication");
    }

    Matrix result(rows_, other.cols());
    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < other.cols(); ++j) {
                double total = 0.0;
                for (size_t k = 0; k < cols_; ++k) {
                    total += (*this)(i, k) * other(k, j);
                }
                result(i, j) = total;
            }
        }
    };

    size_t block_size = rows_ / num_threads;
    std::vector<std::thread> threads;

    for (size_t t = 0; t < num_threads; ++t) {
        size_t start = t * block_size;
        size_t end = (t == num_threads - 1) ? rows_ : start + block_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}
