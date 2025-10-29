#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

// ������� ��� ����������� ����� �����
int getValidNumber(const std::string& prompt, int min, int max) {
    int number;
    std::cout << prompt;

    while (!(std::cin >> number) || number < min || number > max) {
        std::cout << "������! ������� ����� �� " << min << " �� " << max << ": ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(); // ������� ����� ����� ����� �����
    return number;
}

#endif