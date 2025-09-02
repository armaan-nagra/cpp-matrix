#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>
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

#endif // MATRIX_H
