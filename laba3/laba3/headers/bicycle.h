#ifndef BICYCLE_H
#define BICYCLE_H

#include "transport.h"

class Bicycle : public Transport {
    bool basket;
    int gears;

public:
    Bicycle(const std::string& n, double s, double c, double w, int p,  
        bool b, int g);

    double getTime(double dist) override;
    double getCost(double dist, int people, double weight) override;
    void showInfo() override;
};

#endif