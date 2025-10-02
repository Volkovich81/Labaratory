#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
private:
    mutable int** data = nullptr;
    int rows = 0;
    int cols = 0;

    void freeMemory();

public:
    Matrix() = default;
    Matrix(int rows_, int cols_);
    ~Matrix();

    Matrix(const Matrix& other) = delete;
    Matrix& operator=(const Matrix& other) = delete;

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void inputData() const;
    void print() const;
    void multiplyBy(int multiplier) const;
};

#endif