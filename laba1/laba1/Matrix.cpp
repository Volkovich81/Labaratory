#include "Matrix.h"
#include <iostream>

void Matrix::freeMemory() {
    if (data != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

Matrix::Matrix() : data(nullptr), rows(0), cols(0) {}

Matrix::Matrix(int rows_, int cols_) : data(nullptr), rows(0), cols(0) {
    if (rows_ <= 0 || cols_ <= 0) {
        std::cerr << "Ошибка: размеры матрицы должны быть положительными. Создана пустая матрица.\n";
        return;
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

void Matrix::inputData() const {
    if (data == nullptr) {
        std::cerr << "Матрица не инициализирована для ввода.\n";
        return;
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

void Matrix::multiplyBy(int multiplier) const {
    if (data == nullptr) {
        std::cerr << "Матрица не инициализирована для умножения.\n";
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] *= multiplier;
        }
    }
}
