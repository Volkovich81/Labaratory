#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
private:
    mutable int** data;
    int rows;
    int cols;

    void freeMemory();

public:
    Matrix();
    Matrix(int rows_, int cols_);
    ~Matrix();

    int getRows() const;
    int getCols() const;

    void inputData() const;
    void print() const;
    void multiplyBy(int multiplier) const;
};

#endif 

