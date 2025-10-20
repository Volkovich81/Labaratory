#ifndef CARRIAGE_H
#define CARRIAGE_H

#include "transport.h"

class Carriage : public Transport {
    int horses;
    bool covered;

public:
    Carriage(const std::string& n, double s, double c, double w, int p,  // ← ИСПРАВЛЕНО
        int h, bool cov);

    double getTime(double dist) override;
    double getCost(double dist, int people, double weight) override;
    void showInfo() override;
};

#endif