#include "../headers/menu.h"
#include <iostream>
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        Menu menu;
        menu.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная критическая ошибка!" << std::endl;
        return 1;
    }

    return 0;
}