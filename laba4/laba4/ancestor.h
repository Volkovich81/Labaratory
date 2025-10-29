#ifndef ANCESTOR_H
#define ANCESTOR_H

#include <string>
#include <iostream>

class Ancestor {
protected:
    std::string name;

public:
    Ancestor(const std::string& name = "") : name(name) {}
    virtual ~Ancestor() {}

    virtual void print() const = 0;

    std::string getName() const { return name; }
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
    }

    virtual void input() {
        std::cout << "¬ведите им€: ";
        std::getline(std::cin, name);

        while (name.empty()) {
            std::cout << "»м€ не может быть пустым. ¬ведите им€: ";
            std::getline(std::cin, name);
        }
    }
};

#endif