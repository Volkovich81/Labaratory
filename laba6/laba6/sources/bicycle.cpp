#include "../headers/bicycle.h"
#include <iostream>

Bicycle::Bicycle(const std::string& n, double s, double c, double w, int p,
    bool b, int g)
    : Transport(n, s, c, w, p), basket(b), gears(g) {

}

double Bicycle::getTime(double dist) {
    if (dist < 0) return 0;

    double real_speed = getSpeed();
    if (dist > 10) real_speed = getSpeed() * 0.9;
    if (dist > 20) real_speed = getSpeed() * 0.8;

    return dist / real_speed;
}

double Bicycle::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * getCostKm();
    if (basket && weight > 0) {
        cost += weight * 0.05;
    }
    return cost;
}

void Bicycle::showInfo() {
    std::cout << "ВЕЛОСИПЕД: " << getName() << std::endl;
    std::cout << "  Скорость: " << getSpeed() << " км/ч" << std::endl;
    std::cout << "  Стоимость за км: " << getCostKm() << " руб." << std::endl;
    std::cout << "  Груз: " << getMaxWeight() << " кг" << std::endl;
    std::cout << "  Пассажиры: " << getMaxPeople() << " чел." << std::endl;
    std::cout << "  Корзина: " << (basket ? "есть" : "нет") << std::endl;
    std::cout << "  Передачи: " << gears << std::endl;
}