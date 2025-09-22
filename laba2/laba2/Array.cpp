#include "Array.h"

Array::Array() {}

Array::Array(int n) {
    size = n;
    if (n > 0)
        data = new int[n]();
}

Array::Array(const Array& other) {
    size = other.size;
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
}

void Array::swap(Array& other) noexcept {
    int* tmpData = data;
    data = other.data;
    other.data = tmpData;

    int tmpSize = size;
    size = other.size;
    other.size = tmpSize;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) return *this;
    Array tmp(other);
    swap(tmp);
    return *this;
}

Array::~Array() {
    delete[] data;
}

int Array::getSize() const {
    return size;
}

int Array::get(int index) const {
    if (index < 0 || index >= size || data == nullptr)
        return 0;
    return data[index];
}

int& Array::operator[](int index) {
    static int dummy = 0;
    if (index < 0 || index >= size || data == nullptr) {
        return dummy;
    }
    return data[index];
}

const int& Array::operator[](int index) const {
    static const int dummy = 0;
    if (index < 0 || index >= size || data == nullptr) {
        return dummy;
    }
    return data[index];
}

void Array::set(int index, int value) {
    if (index >= 0 && index < size && data != nullptr)
        data[index] = value;
}

void Array::resize(int newSize) {
    if (newSize == size) return;

    int* newData = nullptr;
    if (newSize > 0) {
        newData = new int[newSize]();
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i)
            newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    size = newSize;
}

Array Array::intersect(const Array& other) const {
    Array result;
    if (size == 0 || other.size == 0)
        return result;

    int maxSize = (size < other.size) ? size : other.size;
    Array temp(maxSize);

    int idx = 0;
    for (int i = 0; i < size; ++i) {
        int elem = data[i];
        bool foundInOther = false;

        for (int j = 0; j < other.size; ++j) {
            if (other.data[j] == elem) {
                foundInOther = true;
                break;
            }
        }

        if (!foundInOther) continue;

        bool alreadyAdded = false;
        for (int k = 0; k < idx; ++k) {
            if (temp.data[k] == elem) {
                alreadyAdded = true;
                break;
            }
        }

        if (!alreadyAdded) {
            temp.data[idx++] = elem;
        }
    }

    result.resize(idx);
    for (int i = 0; i < idx; ++i) {
        result.data[i] = temp.data[i];
    }

    return result;
}

Array Array::operator&(const Array& other) const {
    return intersect(other);
}

std::istream& operator>>(std::istream& is, Array& arr) {
    int n;
    if (!(is >> n)) return is;
    if (n < 0) n = 0;

    arr.resize(n);
    for (int i = 0; i < n; ++i)
        is >> arr.data[i];
    return is;
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "{";
    for (int i = 0; i < arr.size; ++i) {
        os << arr[i];
        if (i < arr.size - 1) os << ", ";
    }
    os << "}";
    return os;
}