#ifndef CHILD_H
#define CHILD_H

#include "ancestor.h"
#include <iostream>

class Child : public Ancestor {
public:
    using Ancestor::Ancestor;  // наследуем конструкторы

    explicit Child(const std::string& name = "") : Ancestor(name) {}  // explicit

    void print() const override {
        std::cout << "–ебенок: " << getName() << std::endl;  // используем getter
    }

    void input() override {
        std::cout << "¬ведите им€ ребенка: ";
        std::string name;
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "»м€ ребенка не может быть пустым. ¬ведите им€: ";
            std::getline(std::cin, name);
        }
        setName(name);
    }
};

#endif