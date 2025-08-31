#include <cstddef>
#include <vector>
#include <iostream>

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


int main(){
    Matrix A(2,3);

    A(0,0) = 1.0;
    A(0,1) = 2.0;
    A(0,2) = 3.0;
    A(1,0) = 4.0;
    A(1,1) = 5.0;
    A(1,2) = 6.0;


    for (size_t i = 0; i < 2; ++i){
        for (size_t j = 0; j < 3; j++){
            std::cout << A(i,j) << (j + 1 < 3 ? ' ' : '\n');
        }
    }
}


