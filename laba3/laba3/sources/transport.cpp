#include "transport.h"
#include <iostream>

Transport::Transport(std::string n, double s, double c, double w, int p) {
    name = n;
    speed = s;
    cost_km = c;
    max_weight = w;
    max_people = p;
}

std::string Transport::getName() {
    return name;
}

double Transport::getSpeed() {
    return speed;
}

double Transport::getCostKm() {
    return cost_km;
}

double Transport::getMaxWeight() {
    return max_weight;
}

int Transport::getMaxPeople() {
    return max_people;
}

bool Transport::checkPeople(int people) {
    return people >= 0 && people <= max_people;
}

bool Transport::checkWeight(double weight) {
    return weight >= 0 && weight <= max_weight;
}
