#ifndef UTILS_H
#define UTILS_H

#include <iostream>

template <typename T>
T getInput(const char* msg)
{
    T value;
    std::cout << msg;

    while (true)
    {
        if (std::cin >> value)
        {
            if (std::cin.get() == '\n')
            {
                return value;
            }
            std::cin.clear();
            while (std::cin.get() != '\n' && !std::cin.eof());
            std::cout << "Error, invalid input. Please try again: ";
        }
        else
        {
            std::cin.clear();
            while (std::cin.get() != '\n' && !std::cin.eof());
            std::cout << "Error, invalid input. Please try again: ";
        }
    }
}

template <typename T>
T findMax(const T* begin, const T* end)
{
    if (begin == end || begin == nullptr || end == nullptr)
    {
        std::cout << "Array is empty or invalid pointers!\n";
        return T();
    }

    T maxVal = *begin;
    for (const T* it = begin + 1; it != end; it++)
    {
        if (*it > maxVal)
        {
            maxVal = *it;
        }
    }
    return maxVal;
}

template <typename T>
void inputArray(T* array, int size)
{
    std::cout << "Input " << size << " elements:\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << "Element " << i + 1 << ": ";
        array[i] = getInput<T>("");
    }
}

template <typename T>
void displayArray(const T* array, int size)
{
    std::cout << "Array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

#endif
