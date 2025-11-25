#include "../headers/filemanager.h"
#include <iostream>
#include <stdexcept>

bool FileManager::writeProductsToFile(Product* products, int count, const std::string& filename) {
    if (products == nullptr || count <= 0) {
        std::cout << "Ошибка: нет данных для сохранения!\n";
        return false;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для записи!\n";
        return false;
    }

    file << count << "\n";

    for (int i = 0; i < count; ++i) {
        file << products[i];
    }

    if (file.fail()) {
        std::cout << "Ошибка при записи в файл!\n";
        file.close();
        return false;
    }

    file.close();
    std::cout << "Данные успешно записаны в файл: " << filename << std::endl;
    return true;
}

bool FileManager::readProductsFromFile(Product* products, int& count, int maxCount, const std::string& filename) {
    if (products == nullptr) {
        std::cout << "Ошибка: массив продуктов не инициализирован!\n";
        return false;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << " для чтения!\n";
        return false;
    }

    std::string temp;
    if (!std::getline(file, temp)) {
        std::cout << "Ошибка: файл пуст или поврежден!\n";
        file.close();
        return false;
    }

    try {
        size_t pos = 0;
        count = std::stoi(temp, &pos);
        if (pos != temp.length() || count <= 0) {
            std::cout << "Ошибка: некорректное количество товаров в файле!\n";
            file.close();
            return false;
        }

        if (count > maxCount) {
            std::cout << "Ошибка: слишком много данных в файле! Максимум: " << maxCount << "\n";
            file.close();
            return false;
        }
    }
    catch (const std::exception&) {
        std::cout << "Ошибка: некорректный формат файла!\n";
        file.close();
        return false;
    }

    for (int i = 0; i < count; ++i) {
        try {
            if (!(file >> products[i])) {
                std::cout << "Ошибка при чтении товара №" << (i + 1) << "!\n";
                file.close();
                return false;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при чтении товара №" << (i + 1) << ": " << e.what() << "\n";
            file.close();
            return false;
        }
    }

    if (file.fail() && !file.eof()) {
        std::cout << "Ошибка: проблемы при чтении файла!\n";
        file.close();
        return false;
    }

    file.close();
    std::cout << "Данные успешно прочитаны из файла: " << filename << std::endl;
    return true;
}

int FileManager::getProductsCountByYear(Product* products, int count, int year) {
    if (products == nullptr || count <= 0) {
        return 0;
    }

    int totalCount = 0;
    for (int i = 0; i < count; ++i) {
        if (products[i].getYear() == year) {
            totalCount += products[i].getQuantity();
        }
    }
    return totalCount;
}

void FileManager::displayAllProducts(Product* products, int count) {
    if (products == nullptr || count <= 0) {
        std::cout << "Список товаров пуст.\n";
        return;
    }

    std::cout << "\n=== СПИСОК ВСЕХ ТОВАРОВ ===\n";
    for (int i = 0; i < count; ++i) {
        std::cout << (i + 1) << ". ";
        products[i].display();
    }
    std::cout << "============================\n\n";
}