#include "../headers/transport.h"
#include <iostream>
#include <cctype>

Transport::Transport(const std::string& n, double s, double c, double w, int p)
    : name(n), speed(s), cost_km(c), max_weight(w), max_people(p) {
    validateName(n);
}

std::string Transport::getName() const {
    return name;
}

double Transport::getSpeed() const {
    return speed;
}

double Transport::getCostKm() const {
    return cost_km;
}

double Transport::getMaxWeight() const {
    return max_weight;
}

int Transport::getMaxPeople() const {
    return max_people;
}

bool Transport::checkPeople(int people) const {
    return people >= 0 && people <= max_people;
}

bool Transport::checkWeight(double weight) const {
    return weight >= 0 && weight <= max_weight;
}

void Transport::validateName(const std::string& name) const {
    for (char c : name) {
        if (!(std::isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            throw ValidationException("Ошибка! Название '" + name + "' содержит недопустимые символы. Используйте только цифры и латинские буквы.");
        }
    }
}