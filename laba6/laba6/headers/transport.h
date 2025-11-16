#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>
#include "validation_exception.h"

class Transport {
private:
    std::string name;
    double speed;
    double cost_km;
    double max_weight;
    int max_people;

public:
    Transport(const std::string& n, double s, double c, double w, int p);
    virtual ~Transport() = default;

    virtual double getTime(double dist) = 0;
    virtual double getCost(double dist, int people, double weight) = 0;
    virtual void showInfo() = 0;

    std::string getName() const;
    double getSpeed() const;
    double getCostKm() const;
    double getMaxWeight() const;
    int getMaxPeople() const;

    bool checkPeople(int people) const;
    bool checkWeight(double weight) const;

protected:
    void validateName(const std::string& name) const;
};

#endif