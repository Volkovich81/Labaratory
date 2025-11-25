#pragma once
#ifndef MENU_H
#define MENU_H

#include "product.h"
#include "filemanager.h"
#include <array>

class Menu {
private:
    static const int MAX_PRODUCTS = 100;
    std::array<Product, MAX_PRODUCTS> products;
    int productCount = 0;
    std::string filename = "products.txt";

    int getIntInput(const std::string& prompt, int min, int max);
    double getDoubleInput(const std::string& prompt, double min);
    void clearInputBuffer();

public:
    Menu() = default;
    void run();
    void showMainMenu() const;
    void addProduct();
    void displayProducts() const;
    void saveToFile();
    void loadFromFile();
    void countByYear(); 
};

#endif