#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <fstream>
#include <array>

class Product {
private:
    std::string name;
    int quantity;
    double price;
    int year;
    int month;
    int day;

    bool isValidDate(int y, int m, int d) const;
    bool isValidQuantity(int q) const;
    bool isValidPrice(double p) const;

public:
    Product();
    Product(const std::string& n, int q, double p, int y, int m, int d);

    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    bool setName(const std::string& n);
    bool setQuantity(int q);
    bool setPrice(double p);
    bool setDate(int y, int m, int d);

    void display() const;

    // Объявления дружественных функций
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
    friend std::ofstream& operator<<(std::ofstream& ofs, const Product& product);
    friend std::ifstream& operator>>(std::ifstream& ifs, Product& product);
};

#endif