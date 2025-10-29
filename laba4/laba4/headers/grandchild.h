#ifndef GRANDCHILD_H
#define GRANDCHILD_H

#include "child.h"
#include <iostream>

class Grandchild : public Child {
private:
    std::string patronymic;

public:
    explicit Grandchild(const std::string& name = "", const std::string& patronymic = "")  // explicit
        : Child(name), patronymic(patronymic) {
    }

    void print() const override {
        std::cout << "¬нук: " << getName() << " " << patronymic << std::endl;  // используем getter
    }

    std::string getPatronymic() const { return patronymic; }

    void setPatronymic(const std::string& newPatronymic) {  // const string&
        if (!newPatronymic.empty()) {
            patronymic = newPatronymic;
        }
    }

    void input() override {
        std::cout << "¬ведите им€ внука: ";
        std::string name;
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "»м€ внука не может быть пустым. ¬ведите им€: ";
            std::getline(std::cin, name);
        }
        setName(name);

        std::cout << "¬ведите отчество внука: ";
        std::getline(std::cin, patronymic);

        while (patronymic.empty()) {
            std::cout << "ќтчество не может быть пустым. ¬ведите отчество: ";
            std::getline(std::cin, patronymic);
        }
    }
};

#endif