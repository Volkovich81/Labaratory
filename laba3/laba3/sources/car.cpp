#include "car.h"
#include <iostream>

Car::Car(const std::string& n, double s, double c, double w, int p,  // ← ИСПРАВЛЕНО
    const std::string& f, double fu)  // ← ИСПРАВЛЕНО
    : Transport(n, s, c, w, p), fuel(f), fuel_use(fu) {  // ← ИСПРАВЛЕНО
}

double Car::getTime(double dist) {
    if (dist < 0) return 0;
    return dist / getSpeed();
}

double Car::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * getCostKm();
    if (weight > 0) {
        cost += weight * 0.1;
    }
    return cost;
}

void Car::showInfo() {
    std::cout << "АВТОМОБИЛЬ: " << getName() << std::endl;
    std::cout << "  Скорость: " << getSpeed() << " км/ч" << std::endl;
    std::cout << "  Стоимость за км: " << getCostKm() << " руб." << std::endl;
    std::cout << "  Груз: " << getMaxWeight() << " кг" << std::endl;
    std::cout << "  Пассажиры: " << getMaxPeople() << " чел." << std::endl;
    std::cout << "  Топливо: " << fuel << std::endl;
    std::cout << "  Расход: " << fuel_use << " л/100км" << std::endl;
}