#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "product.h"

class FileManager {
public:
    static bool writeProductsToFile(Product* products, int count, const std::string& filename);
    static bool readProductsFromFile(Product* products, int& count, int maxCount, const std::string& filename);
    static int getProductsCountByYear(Product* products, int count, int year);
    static void displayAllProducts(Product* products, int count);
};

#endif
