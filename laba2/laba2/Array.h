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
    int get(int index) const;
    void set(int index, int value);
    void resize(int newSize);

    Array intersect(const Array& other) const;

    // Исправление: делаем оператор & hidden friend
    friend Array operator&(const Array& lhs, const Array& rhs) {
        return lhs.intersect(rhs);
    }

    int& operator[](int index);
    const int& operator[](int index) const;

    friend std::istream& operator>>(std::istream& is, Array& arr) {
        int n;
        if (!(is >> n)) return is;
        if (n < 0) n = 0;

        arr.resize(n);
        for (int i = 0; i < n; ++i)
            is >> arr.data[i];
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "{";
        for (int i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) os << ", ";
        }
        os << "}";
        return os;
    }

private:
    void swap(Array& other) noexcept;
};

#endif