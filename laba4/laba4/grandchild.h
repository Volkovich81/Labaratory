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
        std::cout << "����: " << name << " " << patronymic << std::endl;
    }

    std::string getPatronymic() const { return patronymic; }
    void setPatronymic(const std::string& newPatronymic) {
        if (!newPatronymic.empty()) {
            patronymic = newPatronymic;
        }
    }

    void input() override {
        std::cout << "������� ��� �����: ";
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "��� ����� �� ����� ���� ������. ������� ���: ";
            std::getline(std::cin, name);
        }

        std::cout << "������� �������� �����: ";
        std::getline(std::cin, patronymic);

        while (patronymic.empty()) {
            std::cout << "�������� �� ����� ���� ������. ������� ��������: ";
            std::getline(std::cin, patronymic);
        }
    }
};

#endif