#include "../headers/Array.h"

Array::Array(int n) : size(n > 0 ? n : 0), data(n > 0 ? new int[n]() : nullptr) {}

Array::Array(const Array& other)
    : size(other.size),
    data(other.size > 0 ? new int[other.size] : nullptr)
{
    if (data != nullptr) {
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

void Array::swap(Array& other) noexcept {
    int* tempData = data;
    data = other.data;
    other.data = tempData;

    int tempSize = size;
    size = other.size;
    other.size = tempSize;
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

/*Array Array::unite(const Array& other) const {
    Array result;

    int totalSize = size + other.size;
    Array temp(totalSize);

    int idx = 0;
    for (int i = 0; i < size; ++i) {
        int elem = data[i];
        bool alreadyAdded = false;

        for (int j = 0; j < idx; ++j) {
            if (temp[j] == elem) {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded) {
            temp[idx] = elem;
            idx++;
        }
    }

    for (int i = 0; i < other.size; ++i) {
        int elem2 = other.data[i];
        bool foundInFirst = false;

        for (int j = 0; j < size; ++j) {
            if (data[j] == elem2) {
                foundInFirst = true;
                break;
            }
        }
        if (!foundInFirst) {
            bool alreadyAdded = false;
            for (int j = 0; j < idx; ++j) {
                if (temp[j] == elem2) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                temp[idx] = elem2;
                idx++;
            }
        }
    }
    result.resize(idx);
    for (int i = 0; i < idx; ++i) {
        result.data[i] = temp.data[i];
    }
    return result;
}*/


/*Array Array::concat(const Array& other) const {
    Array result;

    int totalSize = size + other.size;
    result.resize(totalSize);

    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i];
    }

    for (int i = 0; i < other.size; ++i) {
        result.data[size + i] = other.data[i];
    }

    return result;
}*/








