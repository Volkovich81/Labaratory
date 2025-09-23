#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int** data = nullptr;
    int rows = 0;
    int cols = 0;

    void freeMemory();

public:
    Matrix() = default;
    Matrix(int rows_, int cols_);
    ~Matrix();

    // ������ ����������� � ������������
    Matrix(const Matrix& other) = delete;
    Matrix& operator=(const Matrix& other) = delete;

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void inputData();
    void print() const;
    void multiplyBy(int multiplier);
};

#endif