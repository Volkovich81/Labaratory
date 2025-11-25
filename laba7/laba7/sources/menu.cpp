#include "../headers/menu.h"
#include <iostream>
#include <limits>
#include <stdexcept>

Menu::Menu() : productCount(0), filename("products.txt") {}

void Menu::run() {
    while (true) {
        showMainMenu();
        int choice = getIntInput("Выберите действие", 0, 5);

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            displayProducts();
            break;
        case 3:
            saveToFile();
            break;
        case 4:
            loadFromFile();
            break;
        case 5:
            countByYear();
            break;
        case 0:
            std::cout << "Выход из программы...\n";
            return;
        default:
            std::cout << "Неверный выбор!\n";
            break;
        }
    }
}

void Menu::showMainMenu() {
    std::cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ТОВАРАМИ ===\n";
    std::cout << "1. Добавить товар\n";
    std::cout << "2. Показать все товары\n";
    std::cout << "3. Сохранить в файл\n";
    std::cout << "4. Загрузить из файла\n";
    std::cout << "5. Количество товара по году\n";
    std::cout << "0. Выход\n";
    std::cout << "================================\n";
}

int Menu::getIntInput(const std::string& prompt, int min, int max) {
    int value = 0;
    while (true) {
        std::cout << prompt << " (" << min << "-" << max << "): ";
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка: введите целое число!\n";
        }
        else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << min << " до " << max << "!\n";
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

double Menu::getDoubleInput(const std::string& prompt, double min) {
    double value = 0.0;
    while (true) {
        std::cout << prompt << " (мин. " << min << "): ";
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Ошибка: введите число!\n";
        }
        else if (value < min) {
            std::cout << "Ошибка: число не может быть меньше " << min << "!\n";
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

void Menu::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        std::cout << "Ошибка: достигнуто максимальное количество товаров (" << MAX_PRODUCTS << ")!\n";
        return;
    }

    std::cout << "\n--- ДОБАВЛЕНИЕ НОВОГО ТОВАРА ---\n";
    Product product;
    std::cin >> product;
    products[productCount] = product;
    productCount++;
    std::cout << "Товар успешно добавлен!\n";
}

void Menu::displayProducts() {
    FileManager::displayAllProducts(products, productCount);
}

void Menu::saveToFile() {
    if (productCount <= 0) {
        std::cout << "Нет данных для сохранения!\n";
        return;
    }

    std::cout << "Введите имя файла для сохранения (по умолчанию: " << filename << "): ";
    std::string inputFilename;
    std::getline(std::cin, inputFilename);

    if (!inputFilename.empty()) {
        filename = inputFilename;
    }

    if (FileManager::writeProductsToFile(products, productCount, filename)) {
        std::cout << "Данные успешно сохранены!\n";
    }
}

void Menu::loadFromFile() {
    std::cout << "Введите имя файла для загрузки (по умолчанию: " << filename << "): ";
    std::string inputFilename;
    std::getline(std::cin, inputFilename);

    if (!inputFilename.empty()) {
        filename = inputFilename;
    }

    int loadedCount = 0;
    if (FileManager::readProductsFromFile(products, loadedCount, MAX_PRODUCTS, filename)) {
        productCount = loadedCount;
        std::cout << "Данные успешно загружены! Загружено товаров: " << productCount << std::endl;
    }
}

void Menu::countByYear() {
    if (productCount <= 0) {
        std::cout << "Нет данных для анализа!\n";
        return;
    }

    int year = getIntInput("Введите год для поиска", 1900, 2100);
    int count = FileManager::getProductsCountByYear(products, productCount, year);

    std::cout << "Общее количество товаров " << year << " года выпуска: " << count << std::endl;
}