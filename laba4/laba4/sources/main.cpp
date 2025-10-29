#include <iostream>
#include "../headers/ancestor.h"
#include "../headers/child.h"
#include "../headers/grandchild.h"
#include "../headers/functions.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Child child;
    Grandchild grandchild;

    int choice;

    do {
        std::cout << "\n=== Меню ===" << std::endl;
        std::cout << "1. Ввести данные ребенка" << std::endl;
        std::cout << "2. Ввести данные внука" << std::endl;
        std::cout << "3. Показать данные ребенка" << std::endl;
        std::cout << "4. Показать данные внука" << std::endl;
        std::cout << "0. Выход" << std::endl;

        choice = getValidNumber("Выберите действие: ", 0, 4);

        switch (choice) {
        case 1: {
            std::cout << "\n--- Ввод данных ребенка ---" << std::endl;
            child.input();
            std::cout << "Данные ребенка сохранены!" << std::endl;
            break;
        }

        case 2: {
            std::cout << "\n--- Ввод данных внука ---" << std::endl;
            grandchild.input();
            std::cout << "Данные внука сохранены!" << std::endl;
            break;
        }

        case 3: {
            std::cout << "\n--- Данные ребенка ---" << std::endl;
            if (!child.getName().empty()) {
                child.print();
            }
            else {
                std::cout << "Данные ребенка не введены!" << std::endl;
            }
            break;
        }

        case 4: {
            std::cout << "\n--- Данные внука ---" << std::endl;
            if (!grandchild.getName().empty()) {
                grandchild.print();
            }
            else {
                std::cout << "Данные внука не введены!" << std::endl;
            }
            break;
        }

        case 0: {
            std::cout << "Выход..." << std::endl;
            break;
        }

        default: {  // добавляем default case
            std::cout << "Неверный выбор!" << std::endl;
            break;
        }
        }

    } while (choice != 0);

    return 0;
}