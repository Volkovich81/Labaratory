#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int** data = nullptr;
    int rows = 0;
    int cols = 0;

    void freeMemory();

public:
    Matrix();
    Matrix(int rows_, int cols_);
    ~Matrix();

    // Запрет копирования и присваивания
    Matrix(const Matrix& other) = delete;
    Matrix& operator=(const Matrix& other) = delete;

    int getRows() const;
    int getCols() const;

    void inputData();
    void print() const;
    void multiplyBy(int multiplier);
};

#endif