#include "car.h"
#include <iostream>

Car::Car(std::string n, double s, double c, double w, int p,
    std::string f, double fu)
    : Transport(n, s, c, w, p) {
    fuel = f;
    fuel_use = fu;
}

double Car::getTime(double dist) {
    if (dist < 0) return 0;
    return dist / speed;
}

double Car::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * cost_km;
    if (weight > 0) {
        cost += weight * 0.1;
    }
    return cost;
}

void Car::showInfo() {
    std::cout << "АВТОМОБИЛЬ: " << name << std::endl;
    std::cout << "  Скорость: " << speed << " км/ч" << std::endl;
    std::cout << "  Стоимость за км: " << cost_km << " руб." << std::endl;
    std::cout << "  Груз: " << max_weight << " кг" << std::endl;
    std::cout << "  Пассажиры: " << max_people << " чел." << std::endl;
    std::cout << "  Топливо: " << fuel << std::endl;
    std::cout << "  Расход: " << fuel_use << " л/100км" << std::endl;
}