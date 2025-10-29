#ifndef GRANDCHILD_H
#define GRANDCHILD_H

#include "child.h"
#include <iostream>

class Grandchild : public Child {
private:
    std::string patronymic;

public:
    Grandchild(const std::string& name = "", const std::string& patronymic = "")
        : Child(name), patronymic(patronymic) {
    }

    void print() const override {
        std::cout << "Внук: " << name << " " << patronymic << std::endl;
    }

    std::string getPatronymic() const { return patronymic; }

    void setPatronymic(const std::string& newPatronymic) {
        if (!newPatronymic.empty()) {
            patronymic = newPatronymic;
        }
    }

    void input() override {
        // Ввод имени
        while (true) {
            std::cout << "Введите имя внука: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "Ошибка: Имя внука не может быть пустым!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(name)) {
                std::cout << "Ошибка: Имя должно содержать только буквы!" << std::endl;
                continue;
            }

            break;
        }

        // Ввод отчества
        while (true) {
            std::cout << "Введите отчество внука: ";
            std::getline(std::cin, patronymic);

            if (patronymic.empty()) {
                std::cout << "Ошибка: Отчество не может быть пустым!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(patronymic)) {
                std::cout << "Ошибка: Отчество должно содержать только буквы!" << std::endl;
                continue;
            }

            break;
        }
    }
};

#endif