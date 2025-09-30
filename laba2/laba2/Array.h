#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int size = 0;
    int* data = nullptr;

public:
    Array() = default;
    explicit Array(int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    int getSize() const { return size; }
    void set(int index, int value); // Добавляем метод set

    // Оператор & для пересечения
    friend Array operator&(const Array& lhs, const Array& rhs);

    // Friend функции для ввода-вывода
    friend std::istream& operator>>(std::istream& is, Array& arr);
    friend std::ostream& operator<<(std::ostream& os, const Array& arr);

private:
    void freeMemory();
};

#endif