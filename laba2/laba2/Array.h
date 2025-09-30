#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
private:
    int size = 0;
    int* data = nullptr;
    void freeMemory();

public:
    Array() = default;
    explicit Array(int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    int getSize() const { return size; }
    void set(int index, int value);

    // Hidden friends
    friend Array operator&(const Array& lhs, const Array& rhs);
    friend std::istream& operator>>(std::istream& is, Array& arr);
    friend std::ostream& operator<<(std::ostream& os, const Array& arr);
};

#endif