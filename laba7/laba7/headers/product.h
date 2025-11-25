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

    // Скрытые дружественные операторы
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << product.name << " " << product.quantity << " " << product.price
            << " " << product.year << " " << product.month << " " << product.day;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Product& product) {
        std::string input;

        // Ввод наименования
        while (true) {
            std::cout << "Введите наименование товара: ";
            if (std::getline(is, input) && !input.empty()) {
                product.name = input;
                break;
            }
            std::cout << "Ошибка: наименование не может быть пустым!\n";
        }

        // Ввод количества
        product.quantity = Product::readIntegerInput(is, "Введите количество: ", 0, 10000);

        // Ввод цены
        product.price = Product::readDoubleInput(is, "Введите цену: ", 0.0);

        // Ввод даты
        int year = 0;
        int month = 0;
        int day = 0;
        Product::readDateInput(is, year, month, day);
        product.year = year;
        product.month = month;
        product.day = day;

        return is;
    }

    friend std::ofstream& operator<<(std::ofstream& ofs, const Product& product) {
        ofs << product.name << "\n" << product.quantity << "\n" << product.price << "\n"
            << product.year << "\n" << product.month << "\n" << product.day << "\n";
        return ofs;
    }

    friend std::ifstream& operator>>(std::ifstream& ifs, Product& product) {
        std::string temp;

        if (!std::getline(ifs, product.name)) return ifs;
        if (!std::getline(ifs, temp)) return ifs;
        product.quantity = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.price = std::stod(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.year = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.month = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.day = std::stoi(temp);

        return ifs;
    }

private:
    // Вспомогательные статические методы
    static bool isInteger(const std::string& str);
    static bool isNumber(const std::string& str);
    static int readIntegerInput(std::istream& is, const std::string& prompt, int min, int max);
    static double readDoubleInput(std::istream& is, const std::string& prompt, double min);
    static void readDateInput(std::istream& is, int& year, int& month, int& day);
};

#endif