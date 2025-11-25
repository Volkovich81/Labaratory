#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "product.h"
#include <array>

class FileManager {
public:
    static bool writeProductsToFile(const Product* products, int count, const std::string& filename);
    static bool readProductsFromFile(Product* products, int& count, int maxCount, const std::string& filename);
    static int getProductsCountByYear(const Product* products, int count, int year);
    static void displayAllProducts(const Product* products, int count);
};

#endif