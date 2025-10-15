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

    double real_speed = speed;
    if (dist > 15) real_speed = speed * 0.85;
    if (dist > 30) real_speed = speed * 0.7;

    return dist / real_speed;
}

double Carriage::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * cost_km;
    cost += horses * 2.0;
    if (covered) {
        cost += 5.0;
    }
    return cost;
}

void Carriage::showInfo() {
    std::cout << "ПОВОЗКА: " << name << std::endl;
    std::cout << "  Скорость: " << speed << " км/ч" << std::endl;
    std::cout << "  Стоимость за км: " << cost_km << " руб." << std::endl;
    std::cout << "  Груз: " << max_weight << " кг" << std::endl;
    std::cout << "  Пассажиры: " << max_people << " чел." << std::endl;
    std::cout << "  Лошади: " << horses << std::endl;
    std::cout << "  Крытая: " << (covered ? "да" : "нет") << std::endl;
}