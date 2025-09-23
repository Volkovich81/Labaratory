#include <iostream>
#include <string>
#include <clocale>
#include <stdexcept>
#include <limits>
#include "Matrix.h"

int inputPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Please enter a positive integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    try {
        int rows = inputPositiveInt("Enter number of rows: ");
        int cols = inputPositiveInt("Enter number of columns: ");
        Matrix matrix(rows, cols);

        bool running = true;
        while (running) {
            std::cout << "\nMenu:\n";
            std::cout << "1. Enter matrix elements\n";
            std::cout << "2. Print matrix\n";
            std::cout << "3. Multiply matrix by number\n";
            std::cout << "4. Exit\n";
            std::cout << "Choose action: ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cout << "Input error. Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1:
                try {
                    matrix.inputData();
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            case 2:
                matrix.print();
                break;
            case 3: {
                try {
                    int multiplier = inputPositiveInt("Enter multiplier: ");
                    matrix.multiplyBy(multiplier);
                    std::cout << "Multiplication result:\n";
                    matrix.print();
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 4:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}