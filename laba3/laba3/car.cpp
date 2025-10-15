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
    std::cout << "����������: " << name << std::endl;
    std::cout << "  ��������: " << speed << " ��/�" << std::endl;
    std::cout << "  ��������� �� ��: " << cost_km << " ���." << std::endl;
    std::cout << "  ����: " << max_weight << " ��" << std::endl;
    std::cout << "  ���������: " << max_people << " ���." << std::endl;
    std::cout << "  �������: " << fuel << std::endl;
    std::cout << "  ������: " << fuel_use << " �/100��" << std::endl;
}