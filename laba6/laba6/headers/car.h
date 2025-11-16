#ifndef CAR_H
#define CAR_H

#include "transport.h"

class Car : public Transport {
    std::string fuel;
    double fuel_use;

public:
    Car(const std::string& n, double s, double c, double w, int p,
        const std::string& f, double fu);

    double getTime(double dist) override;
    double getCost(double dist, int people, double weight) override;
    void showInfo() override;
};

#endif