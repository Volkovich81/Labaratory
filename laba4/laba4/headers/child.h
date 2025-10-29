#ifndef CHILD_H
#define CHILD_H

#include "ancestor.h"
#include <iostream>

class Child : public Ancestor {
public:
    using Ancestor::Ancestor;

    void print() const override {
        std::cout << "�������: " << getName() << std::endl;
    }

    void input() override {
        std::cout << "������� ��� �������: ";
        std::string name;
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "��� ������� �� ����� ���� ������. ������� ���: ";
            std::getline(std::cin, name);
        }
        setName(name);
    }
};

#endif