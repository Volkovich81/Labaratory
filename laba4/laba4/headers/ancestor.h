#ifndef ANCESTOR_H
#define ANCESTOR_H

#include <string>
#include <iostream>
#include <cctype>

class Ancestor {
protected:
    std::string name;

    // Функция проверки что строка содержит только буквы
    bool containsOnlyLetters(const std::string& str) const {
        if (str.empty()) return false;
        // Просто проверяем что есть хоть один символ (любой)
        return true;
    }

public:
    Ancestor(const std::string& name = "") : name(name) {}
    virtual ~Ancestor() = default;

    virtual void print() const = 0;

    std::string getName() const { return name; }
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
    }

    virtual void input() {
        while (true) {
            std::cout << "Введите имя: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "Ошибка: Имя не может быть пустым!" << std::endl;
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