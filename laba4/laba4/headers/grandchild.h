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
        // ���� �����
        while (true) {
            std::cout << "������� ��� �����: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "������: ��� ����� �� ����� ���� ������!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(name)) {
                std::cout << "������: ��� ������ ��������� ������ �����!" << std::endl;
                continue;
            }

            break;
        }

        // ���� ��������
        while (true) {
            std::cout << "������� �������� �����: ";
            std::getline(std::cin, patronymic);

            if (patronymic.empty()) {
                std::cout << "������: �������� �� ����� ���� ������!" << std::endl;
                continue;
            }

            if (!containsOnlyLetters(patronymic)) {
                std::cout << "������: �������� ������ ��������� ������ �����!" << std::endl;
                continue;
            }

            break;
        }
    }
};

#endif