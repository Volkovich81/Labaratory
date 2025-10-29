#ifndef CHILD_H
#define CHILD_H

#include "ancestor.h"
#include <iostream>

class Child : public Ancestor {
public:
    Child(const std::string& name = "") : Ancestor(name) {}

    void print() const override {
        std::cout << "–ебенок: " << name << std::endl;
    }

    void input() override {
        std::cout << "¬ведите им€ ребенка: ";
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "»м€ ребенка не может быть пустым. ¬ведите им€: ";
            std::getline(std::cin, name);
        }
    }
};

#endif