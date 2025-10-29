#include <iostream>
#include <array>
#include "../headers/ancestor.h"
#include "../headers/child.h"
#include "../headers/grandchild.h"
#include "../headers/functions.h"

#ifdef _WIN32
#include <windows.h>
#endif

void showAllChildren(const std::array<Child, MAX_OBJECTS>& children, int count) {
    std::cout << "\n--- Все дети (" << count << ") ---" << std::endl;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            std::cout << (i + 1) << ". ";
            children[i].print();
        }
    }
    else {
        std::cout << "Дети не введены!" << std::endl;
    }
}

void showAllGrandchildren(const std::array<Grandchild, MAX_OBJECTS>& grandchildren, int count) {
    std::cout << "\n--- Все внуки (" << count << ") ---" << std::endl;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            std::cout << (i + 1) << ". ";
            grandchildren[i].print();
        }
    }
    else {
        std::cout << "Внуки не введены!" << std::endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::array<Child, MAX_OBJECTS> children;
    std::array<Grandchild, MAX_OBJECTS> grandchildren;
    int childCount = 0;
    int grandchildCount = 0;

    int choice;

    do {
        std::cout << "\n=== Меню ===" << std::endl;
        std::cout << "1. Ввести данные ребенка" << std::endl;
        std::cout << "2. Ввести данные внука" << std::endl;
        std::cout << "3. Показать всех детей" << std::endl;
        std::cout << "4. Показать всех внуков" << std::endl;
        std::cout << "0. Выход" << std::endl;

        choice = getValidNumber("Выберите действие: ", 0, 4);

        switch (choice) {
        case 1: {
            if (childCount < MAX_OBJECTS) {
                std::cout << "\n--- Ввод данных ребенка " << (childCount + 1) << " ---" << std::endl;
                children[childCount].input();
                childCount++;
                std::cout << "Данные ребенка сохранены!" << std::endl;
            }
            else {
                std::cout << "Достигнут максимум детей (" << MAX_OBJECTS << ")!" << std::endl;
            }
            break;
        }

        case 2: {
            if (grandchildCount < MAX_OBJECTS) {
                std::cout << "\n--- Ввод данных внука " << (grandchildCount + 1) << " ---" << std::endl;
                grandchildren[grandchildCount].input();
                grandchildCount++;
                std::cout << "Данные внука сохранены!" << std::endl;
            }
            else {
                std::cout << "Достигнут максимум внуков (" << MAX_OBJECTS << ")!" << std::endl;
            }
            break;
        }

        case 3: {
            showAllChildren(children, childCount);
            break;
        }

        case 4: {
            showAllGrandchildren(grandchildren, grandchildCount);
            break;
        }

        case 0: {
            std::cout << "Выход..." << std::endl;
            break;
        }

        default: {
            std::cout << "Неверный выбор!" << std::endl;
            break;
        }
        }

    } while (choice != 0);

    return 0;
}