#ifndef CHILD_H
#define CHILD_H

#include "ancestor.h"
#include <iostream>

class Child : public Ancestor {
public:
    Child(const std::string& name = "") : Ancestor(name) {}

    void print() const override {
        std::cout << "Ребенок: " << name << std::endl;
    }

    void input() override {
        while (true) {
            std::cout << "Введите имя ребенка: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "Ошибка: Имя ребенка не может быть пустым!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(name)) {
                std::cout << "Ошибка: Имя должно содержать только буквы!" << std::endl;
                continue;
            }

            break;
        }
    }
};

#endif