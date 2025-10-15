#include "bicycle.h"
#include <iostream>

Bicycle::Bicycle(std::string n, double s, double c, double w, int p,
    bool b, int g)
    : Transport(n, s, c, w, p) {
    basket = b;
    gears = g;
}

double Bicycle::getTime(double dist) {
    if (dist < 0) return 0;

    double real_speed = speed;
    if (dist > 10) real_speed = speed * 0.9;
    if (dist > 20) real_speed = speed * 0.8;

    return dist / real_speed;
}

double Bicycle::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * cost_km;
    if (basket && weight > 0) {
        cost += weight * 0.05;
    }
    return cost;
}

void Bicycle::showInfo() {
    std::cout << "ВЕЛОСИПЕД: " << name << std::endl;
    std::cout << "  Скорость: " << speed << " км/ч" << std::endl;
    std::cout << "  Стоимость за км: " << cost_km << " руб." << std::endl;
    std::cout << "  Груз: " << max_weight << " кг" << std::endl;
    std::cout << "  Пассажиры: " << max_people << " чел." << std::endl;
    std::cout << "  Корзина: " << (basket ? "есть" : "нет") << std::endl;
    std::cout << "  Передачи: " << gears << std::endl;
}