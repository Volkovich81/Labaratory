#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

// Функция для безопасного ввода числа
int getValidNumber(const std::string& prompt, int min, int max) {
    int number;
    std::cout << prompt;

    while (!(std::cin >> number) || number < min || number > max) {
        std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(); // Очищаем буфер после ввода числа
    return number;
}

#endif