#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <limits>

// Пользовательские исключения
class MatrixInvalidSizeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Matrix dimensions must be positive";
    }
};

class MatrixNotInitializedException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Matrix is not initialized";
    }
};

class MatrixInputException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Matrix input error";
    }
};

void Matrix::freeMemory() {
    if (data != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
        rows = 0;
        cols = 0;
    }
}

Matrix::Matrix(int rows_, int cols_) {
    if (rows_ <= 0 || cols_ <= 0) {
        throw MatrixInvalidSizeException();
    }

    rows = rows_;
    cols = cols_;
    data = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new int[cols] {};
    }
}

Matrix::~Matrix() {
    freeMemory();
}

void Matrix::inputData() {
    if (data == nullptr) {
        throw MatrixNotInitializedException();
    }

    std::cout << "Enter matrix elements (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Element [" << i << "][" << j << "]: ";
            if (!(std::cin >> data[i][j])) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw MatrixInputException();
            }
        }
    }
}

void Matrix::print() const {
    if (data == nullptr) {
        std::cout << "Empty matrix.\n";
        return;
    }

    std::cout << "Matrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

void Matrix::multiplyBy(int multiplier) {
    if (data == nullptr) {
        throw MatrixNotInitializedException();
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] *= multiplier;
        }
    }
}