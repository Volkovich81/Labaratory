#include "../headers/product.h"
#include <limits>
#include <stdexcept>
#include <cctype>
#include <array>

Product::Product() : name(""), quantity(0), price(0.0), year(2000), month(1), day(1) {}

Product::Product(const std::string& n, int q, double p, int y, int m, int d) :
    name(n), quantity(q), price(p), year(y), month(m), day(d) {
}

bool Product::isValidDate(int y, int m, int d) const {
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;

    const std::array<int, 12> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    const int maxDays = (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)))
        ? 29 : daysInMonth[m - 1];

    return (d >= 1 && d <= maxDays);
}

bool Product::isValidQuantity(int q) const {
    return q >= 0;
}

bool Product::isValidPrice(double p) const {
    return p >= 0.0;
}

bool Product::setName(const std::string& n) {
    if (!n.empty()) {
        name = n;
        return true;
    }
    return false;
}

bool Product::setQuantity(int q) {
    if (isValidQuantity(q)) {
        quantity = q;
        return true;
    }
    return false;
}

bool Product::setPrice(double p) {
    if (isValidPrice(p)) {
        price = p;
        return true;
    }
    return false;
}

bool Product::setDate(int y, int m, int d) {
    if (isValidDate(y, m, d)) {
        year = y;
        month = m;
        day = d;
        return true;
    }
    return false;
}

void Product::display() const {
    std::cout << "Наименование: " << name
        << ", Количество: " << quantity
        << ", Цена: " << price
        << " руб., Дата поступления: "
        << day << "." << month << "." << year << std::endl;
}

// Вспомогательные статические методы
bool Product::isInteger(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-') {
        if (str.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.length(); i++) {
        if (!isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

bool Product::isNumber(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    bool hasDecimalPoint = false;

    if (str[0] == '-') {
        if (str.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDecimalPoint) return false;
            hasDecimalPoint = true;
        }
        else if (!isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

int Product::readIntegerInput(std::istream& is, const std::string& prompt, int min, int max) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (std::getline(is, input)) {
            if (isInteger(input)) {
                try {
                    const int value = std::stoi(input);
                    if (value >= min && value <= max) {
                        return value;
                    }
                    std::cout << "Ошибка: число должно быть в диапазоне " << min << "-" << max << "!\n";
                }
                catch (const std::invalid_argument&) {
                    std::cout << "Ошибка: введите корректное целое число!\n";
                }
                catch (const std::out_of_range&) {
                    std::cout << "Ошибка: число слишком большое!\n";
                }
            }
            else {
                std::cout << "Ошибка: введите целое число!\n";
            }
        }
    }
}

double Product::readDoubleInput(std::istream& is, const std::string& prompt, double min) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (std::getline(is, input)) {
            for (char& c : input) {
                if (c == ',') c = '.';
            }

            if (isNumber(input)) {
                try {
                    const double value = std::stod(input);
                    if (value >= min) {
                        return value;
                    }
                    std::cout << "Ошибка: число не может быть меньше " << min << "!\n";
                }
                catch (const std::invalid_argument&) {
                    std::cout << "Ошибка: введите корректное число!\n";
                }
                catch (const std::out_of_range&) {
                    std::cout << "Ошибка: число слишком большое!\n";
                }
            }
            else {
                std::cout << "Ошибка: введите число (можно использовать точку или запятую)!\n";
            }
        }
    }
}

void Product::readDateInput(std::istream& is, int& year, int& month, int& day) {
    year = readIntegerInput(is, "Введите год поступления: ", 1900, 2100);
    month = readIntegerInput(is, "Введите месяц поступления (1-12): ", 1, 12);

    const std::array<int, 12> daysInMonth = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDays = daysInMonth[month - 1];

    if (month == 2) {
        maxDays = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }

    day = readIntegerInput(is, "Введите день поступления: ", 1, maxDays);
}