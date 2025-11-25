#include "../headers/product.h"
#include <limits>
#include <stdexcept>
#include <cctype>
#include <array>

Product::Product() : name_(""), quantity_(0), price_(0.0), year_(2000), month_(1), day_(1) {}

Product::Product(const std::string& name, int qty, double cost, int yr, int mn, int dy) :
    name_(name), quantity_(qty), price_(cost), year_(yr), month_(mn), day_(dy) {
}

bool Product::isValidDate(int year, int month, int day) const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    const std::array<int, 12> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    const int maxDays = (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        ? 29 : daysInMonth[month - 1];

    return (day >= 1 && day <= maxDays);
}

bool Product::isValidQuantity(int qty) const {
    return qty >= 0;
}

bool Product::isValidPrice(double cost) const {
    return cost >= 0.0;
}

bool Product::setName(const std::string& name) {
    if (!name.empty()) {
        name_ = name;
        return true;
    }
    return false;
}

bool Product::setQuantity(int qty) {
    if (isValidQuantity(qty)) {
        quantity_ = qty;
        return true;
    }
    return false;
}

bool Product::setPrice(double cost) {
    if (isValidPrice(cost)) {
        price_ = cost;
        return true;
    }
    return false;
}

bool Product::setDate(int year, int month, int day) {
    if (isValidDate(year, month, day)) {
        year_ = year;
        month_ = month;
        day_ = day;
        return true;
    }
    return false;
}

void Product::display() const {
    std::cout << "Наименование: " << name_
        << ", Количество: " << quantity_
        << ", Цена: " << price_
        << " руб., Дата поступления: "
        << day_ << "." << month_ << "." << year_ << std::endl;
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

int Product::readIntegerInput(std::istream& is, const std::string& prompt, int minVal, int maxVal) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(is, input)) continue;

        if (!isInteger(input)) {
            std::cout << "Ошибка: введите целое число!\n";
            continue;
        }

        try {
            const int value = std::stoi(input);
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "Ошибка: число должно быть в диапазоне " << minVal << "-" << maxVal << "!\n";
        }
        catch (const std::invalid_argument&) {
            std::cout << "Ошибка: введите корректное целое число!\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Ошибка: число слишком большое!\n";
        }
    }
}

double Product::readDoubleInput(std::istream& is, const std::string& prompt, double minVal) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(is, input)) continue;

        for (char& c : input) {
            if (c == ',') c = '.';
        }

        if (!isNumber(input)) {
            std::cout << "Ошибка: введите число (можно использовать точку или запятую)!\n";
            continue;
        }

        try {
            const double value = std::stod(input);
            if (value >= minVal) {
                return value;
            }
            std::cout << "Ошибка: число не может быть меньше " << minVal << "!\n";
        }
        catch (const std::invalid_argument&) {
            std::cout << "Ошибка: введите корректное число!\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Ошибка: число слишком большое!\n";
        }
    }
}

void Product::readDateInput(std::istream& is, int& outYear, int& outMonth, int& outDay) {
    outYear = readIntegerInput(is, "Введите год поступления: ", 1900, 2100);
    outMonth = readIntegerInput(is, "Введите месяц поступления (1-12): ", 1, 12);

    const std::array<int, 12> daysInMonth = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDays = daysInMonth[outMonth - 1];

    if (outMonth == 2) {
        maxDays = ((outYear % 4 == 0 && outYear % 100 != 0) || (outYear % 400 == 0)) ? 29 : 28;
    }

    outDay = readIntegerInput(is, "Введите день поступления: ", 1, maxDays);
}