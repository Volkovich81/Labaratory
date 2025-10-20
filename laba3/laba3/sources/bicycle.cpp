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

    double real_speed = getSpeed();  // ? »—œ–¿¬À≈ÕŒ
    if (dist > 10) real_speed = getSpeed() * 0.9;  // ? »—œ–¿¬À≈ÕŒ
    if (dist > 20) real_speed = getSpeed() * 0.8;  // ? »—œ–¿¬À≈ÕŒ

    return dist / real_speed;
}

double Bicycle::getCost(double dist, int people, double weight) {
    if (dist < 0) return 0;
    if (!checkPeople(people)) return 0;
    if (!checkWeight(weight)) return 0;

    double cost = dist * getCostKm();  // ? »—œ–¿¬À≈ÕŒ
    if (basket && weight > 0) {
        cost += weight * 0.05;
    }
    return cost;
}

void Bicycle::showInfo() {
    std::cout << "¬≈ÀŒ—»œ≈ƒ: " << getName() << std::endl;  // ? »—œ–¿¬À≈ÕŒ
    std::cout << "  —ÍÓÓÒÚ¸: " << getSpeed() << " ÍÏ/˜" << std::endl;  // ? »—œ–¿¬À≈ÕŒ
    std::cout << "  —ÚÓËÏÓÒÚ¸ Á‡ ÍÏ: " << getCostKm() << " Û·." << std::endl;  // ? »—œ–¿¬À≈ÕŒ
    std::cout << "  √ÛÁ: " << getMaxWeight() << " Í„" << std::endl;  // ? »—œ–¿¬À≈ÕŒ
    std::cout << "  œ‡ÒÒ‡ÊË˚: " << getMaxPeople() << " ˜ÂÎ." << std::endl;  // ? »—œ–¿¬À≈ÕŒ
    std::cout << "   ÓÁËÌ‡: " << (basket ? "ÂÒÚ¸" : "ÌÂÚ") << std::endl;
    std::cout << "  œÂÂ‰‡˜Ë: " << gears << std::endl;
}