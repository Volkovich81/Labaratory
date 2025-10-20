#include "transport.h"
#include <iostream>

Transport::Transport(const std::string& n, double s, double c, double w, int p)
    : name(n), speed(s), cost_km(c), max_weight(w), max_people(p) {
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

void Transport::setSpeed(double s) { speed = s; }
void Transport::setCostKm(double c) { cost_km = c; }
void Transport::setMaxWeight(double w) { max_weight = w; }
void Transport::setMaxPeople(int p) { max_people = p; }