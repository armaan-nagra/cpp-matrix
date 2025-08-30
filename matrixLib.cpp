#include <cstddef>
#include <vector>

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

private: 
    size_t rows_, cols_;
    std::vector<double> data_;
};