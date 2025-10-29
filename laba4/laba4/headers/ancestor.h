#ifndef ANCESTOR_H
#define ANCESTOR_H

#include <string>
#include <iostream>
#include <cctype>

class Ancestor {
protected:
    std::string name;

    // ������� �������� ��� ������ �������� ������ �����
    bool containsOnlyLetters(const std::string& str) const {
        if (str.empty()) return false;
        // ������ ��������� ��� ���� ���� ���� ������ (�����)
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
            std::cout << "������� ���: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "������: ��� �� ����� ���� ������!" << std::endl;
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