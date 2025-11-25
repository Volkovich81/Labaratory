#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <fstream>
#include <array>

class Product {
private:
    std::string name_;
    int quantity_;
    double price_;
    int year_;
    int month_;
    int day_;

    bool isValidDate(int year, int month, int day) const;
    bool isValidQuantity(int qty) const;
    bool isValidPrice(double cost) const;

public:
    Product();
    Product(const std::string& name, int qty, double cost, int yr, int mn, int dy);

    std::string getName() const { return name_; }
    int getQuantity() const { return quantity_; }
    double getPrice() const { return price_; }
    int getYear() const { return year_; }
    int getMonth() const { return month_; }
    int getDay() const { return day_; }

    bool setName(const std::string& name);
    bool setQuantity(int qty);
    bool setPrice(double cost);
    bool setDate(int year, int month, int day);

    void display() const;

    // Все операторы как скрытые друзья
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << product.name_ << " " << product.quantity_ << " " << product.price_
            << " " << product.year_ << " " << product.month_ << " " << product.day_;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Product& product) {
        std::string input;

        // Ввод наименования
        while (true) {
            std::cout << "Введите наименование товара: ";
            if (std::getline(is, input) && !input.empty()) {
                product.name_ = input;
                break;
            }
            std::cout << "Ошибка: наименование не может быть пустым!\n";
        }

        // Ввод количества
        product.quantity_ = Product::readIntegerInput(is, "Введите количество: ", 0, 10000);

        // Ввод цены
        product.price_ = Product::readDoubleInput(is, "Введите цену: ", 0.0);

        // Ввод даты
        int year = 0;
        int month = 0;
        int day = 0;
        Product::readDateInput(is, year, month, day);
        product.year_ = year;
        product.month_ = month;
        product.day_ = day;

        return is;
    }

    friend std::ofstream& operator<<(std::ofstream& ofs, const Product& product) {
        ofs << product.name_ << "\n" << product.quantity_ << "\n" << product.price_ << "\n"
            << product.year_ << "\n" << product.month_ << "\n" << product.day_ << "\n";
        return ofs;
    }

    friend std::ifstream& operator>>(std::ifstream& ifs, Product& product) {
        std::string temp;

        if (!std::getline(ifs, product.name_)) return ifs;
        if (!std::getline(ifs, temp)) return ifs;
        product.quantity_ = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.price_ = std::stod(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.year_ = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.month_ = std::stoi(temp);
        if (!std::getline(ifs, temp)) return ifs;
        product.day_ = std::stoi(temp);

        return ifs;
    }

private:
    // Вспомогательные статические методы
    static bool isInteger(const std::string& str);
    static bool isNumber(const std::string& str);
    static int readIntegerInput(std::istream& is, const std::string& prompt, int minVal, int maxVal);
    static double readDoubleInput(std::istream& is, const std::string& prompt, double minVal);
    static void readDateInput(std::istream& is, int& outYear, int& outMonth, int& outDay);
};

#endif