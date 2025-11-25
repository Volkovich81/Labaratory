#pragma once
#ifndef MENU_H
#define MENU_H

#include "product.h"
#include "filemanager.h"

class Menu {
private:
    static const int MAX_PRODUCTS = 100;
    Product products[MAX_PRODUCTS];
    int productCount;
    std::string filename;

    int getIntInput(const std::string& prompt, int min, int max);
    double getDoubleInput(const std::string& prompt, double min);
    void clearInputBuffer();

public:
    Menu();
    void run();
    void showMainMenu();
    void addProduct();
    void displayProducts();
    void saveToFile();
    void loadFromFile();
    void countByYear();
};

#endif
