#ifndef CHILD_H
#define CHILD_H

#include "ancestor.h"
#include <iostream>

class Child : public Ancestor {
public:
    Child(const std::string& name = "") : Ancestor(name) {}

    void print() const override {
        std::cout << "�������: " << name << std::endl;
    }

    void input() override {
        while (true) {
            std::cout << "������� ��� �������: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "������: ��� ������� �� ����� ���� ������!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(name)) {
                std::cout << "������: ��� ������ ��������� ������ �����!" << std::endl;
                continue;
            }

            break;
        }
    }
};

#endif