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
        std::cout << "����: " << getName() << " " << patronymic << std::endl;  // ���������� getter
    }

    std::string getPatronymic() const { return patronymic; }

    void setPatronymic(const std::string& newPatronymic) {  // const string&
        if (!newPatronymic.empty()) {
            patronymic = newPatronymic;
        }
    }

    void input() override {
        std::cout << "������� ��� �����: ";
        std::string name;
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "��� ����� �� ����� ���� ������. ������� ���: ";
            std::getline(std::cin, name);
        }
        setName(name);

        std::cout << "������� �������� �����: ";
        std::getline(std::cin, patronymic);

        while (patronymic.empty()) {
            std::cout << "�������� �� ����� ���� ������. ������� ��������: ";
            std::getline(std::cin, patronymic);
        }
    }
};

#endif