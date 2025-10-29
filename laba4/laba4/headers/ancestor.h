#ifndef ANCESTOR_H
#define ANCESTOR_H

#include <string>
#include <iostream>

class Ancestor {
private:  // ������ protected �� private
    std::string name;

public:
    explicit Ancestor(const std::string& name = "") : name(name) {}  // explicit
    virtual ~Ancestor() = default;

    virtual void print() const = 0;

    std::string getName() const { return name; }
    void setName(const std::string& newName) {  // const string&
        if (!newName.empty()) {
            name = newName;
        }
    }

    virtual void input() {
        std::cout << "������� ���: ";
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "��� �� ����� ���� ������. ������� ���: ";
            std::getline(std::cin, name);
        }
    }
};

#endif