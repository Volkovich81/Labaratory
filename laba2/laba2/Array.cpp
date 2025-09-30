#include "Array.h"

Array::Array(int n) : size(n > 0 ? n : 0), data(n > 0 ? new int[n]() : nullptr) {}

Array::Array(const Array& other)
    : size(other.size),
    data(other.size > 0 ? new int[other.size] : nullptr)
{
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

void Array::freeMemory() {
    delete[] data;
    data = nullptr;
    size = 0;
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        freeMemory();
        size = other.size;
        if (size > 0) {
            data = new int[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }
    return *this;
}

Array::~Array() {
    freeMemory();
}

void Array::set(int index, int value) {
    if (index >= 0 && index < size && data != nullptr) {
        data[index] = value;
    }
}

// Реализация оператора & для пересечения массивов
Array operator&(const Array& lhs, const Array& rhs) {
    Array result;

    if (lhs.size == 0 || rhs.size == 0) {
        return result;
    }

    // Временный массив для хранения пересечения
    int maxSize = (lhs.size < rhs.size) ? lhs.size : rhs.size;
    int* temp = new int[maxSize];
    int count = 0;

    // Находим пересечение
    for (int i = 0; i < lhs.size; ++i) {
        for (int j = 0; j < rhs.size; ++j) {
            if (lhs.data[i] == rhs.data[j]) {
                // Проверяем, нет ли уже этого элемента в результате
                bool found = false;
                for (int k = 0; k < count; ++k) {
                    if (temp[k] == lhs.data[i]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    temp[count++] = lhs.data[i];
                }
                break;
            }
        }
    }

    // Создаем результирующий массив
    if (count > 0) {
        result.size = count;
        result.data = new int[count];
        for (int i = 0; i < count; ++i) {
            result.data[i] = temp[i];
        }
    }

    delete[] temp;
    return result;
}

// Friend функция для ввода
std::istream& operator>>(std::istream& is, Array& arr) {
    int n;
    if (!(is >> n) || n <= 0) {
        arr.freeMemory();
        return is;
    }

    arr.freeMemory();
    arr.size = n;
    arr.data = new int[n];

    for (int i = 0; i < n; ++i) {
        is >> arr.data[i];
    }
    return is;
}

// Friend функция для вывода
std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "{";
    for (int i = 0; i < arr.size; ++i) {
        os << arr.data[i];
        if (i < arr.size - 1) os << ", ";
    }
    os << "}";
    return os;
}