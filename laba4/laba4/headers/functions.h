#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <array>

const int MAX_OBJECTS = 10;

inline int getValidNumber(const std::string& prompt, const int min, const int max) {
    int number;
    std::cout << prompt;

    while (!(static_cast<bool>(std::cin >> number)) || number < min || number > max) {
        std::cout << "ќшибка! ¬ведите число от " << min << " до " << max << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore();
    return number;
}

#endif