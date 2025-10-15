#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>

class Transport {
protected:
    std::string name;
    double speed;
    double cost_km;
    double max_weight;
    int max_people;

public:
    Transport(std::string n, double s, double c, double w, int p);
    virtual ~Transport() {}

    virtual double getTime(double dist) = 0;
    virtual double getCost(double dist, int people, double weight) = 0;
    virtual void showInfo() = 0;

    std::string getName();
    double getSpeed();
    double getCostKm();
    double getMaxWeight();
    int getMaxPeople();

    bool checkPeople(int people);
    bool checkWeight(double weight);
};

#endif
