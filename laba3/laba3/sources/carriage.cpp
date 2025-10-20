#include "carriage.h"
#include <iostream>

Carriage::Carriage(std::string n, double s, double c, double w, int p,
    int h, bool cov)
    : Transport(n, s, c, w, p) {
    horses = h;
    covered = cov;
}

double Carriage::getTime(double dist) {
    if (dist < 0) return 0;

    double real_speed = getSpeed();  // ← ИСПРАВЛЕНО
    if (dist > 15) real_speed = getSpeed() * 0.85;  // ← ИСПРАВЛЕНО
    if (dist > 30) real_speed = getSpeed() * 0.7;  // ← ИСПРАВЛЕНО

    return dist / real_speed;
}

double Carriage::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * getCostKm();  // ← ИСПРАВЛЕНО
    cost += horses * 2.0;
    if (covered) {
        cost += 5.0;
    }
    return cost;
}

void Carriage::showInfo() {
    std::cout << "ПОВОЗКА: " << getName() << std::endl;  // ← ИСПРАВЛЕНО
    std::cout << "  Скорость: " << getSpeed() << " км/ч" << std::endl;  // ← ИСПРАВЛЕНО
    std::cout << "  Стоимость за км: " << getCostKm() << " руб." << std::endl;  // ← ИСПРАВЛЕНО
    std::cout << "  Груз: " << getMaxWeight() << " кг" << std::endl;  // ← ИСПРАВЛЕНО
    std::cout << "  Пассажиры: " << getMaxPeople() << " чел." << std::endl;  // ← ИСПРАВЛЕНО
    std::cout << "  Лошади: " << horses << std::endl;
    std::cout << "  Крытая: " << (covered ? "да" : "нет") << std::endl;
}