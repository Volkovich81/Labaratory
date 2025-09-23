#include "Matrix.h"
#include <iostream>
#include <stdexcept>

// Пользовательские исключения
class MatrixInvalidSizeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Размеры матрицы должны быть положительными";
    }
};

class MatrixNotInitializedException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Матрица не инициализирована";
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

Matrix::Matrix() {} // Используем инициализаторы в классе

Matrix::Matrix(int rows_, int cols_) {
    if (rows_ <= 0 || cols_ <= 0) {
        throw MatrixInvalidSizeException();
    }

    rows = rows_;
    cols = cols_;
    data = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new int[cols] {0};
    }
}

Matrix::~Matrix() {
    freeMemory();
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

void Matrix::inputData() {
    if (data == nullptr) {
        throw MatrixNotInitializedException();
    }

    std::cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            if (!(std::cin >> data[i][j])) {
                std::cerr << "Ошибка ввода элемента [" << i << "][" << j << "]\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return;
            }
        }
    }
}

void Matrix::print() const {
    if (data == nullptr) {
        std::cout << "Пустая матрица.\n";
        return;
    }

    std::cout << "Матрица (" << rows << "x" << cols << "):\n";
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