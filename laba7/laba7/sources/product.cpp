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
    int maxDays = daysInMonth[m - 1];

    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
        maxDays = 29;
    }

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

// Реализации операторов
std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << product.name << " " << product.quantity << " " << product.price
        << " " << product.year << " " << product.month << " " << product.day;
    return os;
}

std::ofstream& operator<<(std::ofstream& ofs, const Product& product) {
    ofs << product.name << "\n" << product.quantity << "\n" << product.price << "\n"
        << product.year << "\n" << product.month << "\n" << product.day << "\n";
    return ofs;
}

// Вспомогательные функции
namespace {
    bool isInteger(const std::string& str) {
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

    bool isNumber(const std::string& str) {
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

    int readIntegerInput(std::istream& is, const std::string& prompt, int min, int max) {
        std::string input;
        while (true) {
            std::cout << prompt;
            if (std::getline(is, input)) {
                if (isInteger(input)) {
                    try {
                        int value = std::stoi(input);
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

    double readDoubleInput(std::istream& is, const std::string& prompt, double min) {
        std::string input;
        while (true) {
            std::cout << prompt;
            if (std::getline(is, input)) {
                // Заменяем запятую на точку для корректного ввода
                for (char& c : input) {
                    if (c == ',') c = '.';
                }

                if (isNumber(input)) {
                    try {
                        double value = std::stod(input);
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

    void readDateInput(std::istream& is, int& year, int& month, int& day) {
        year = readIntegerInput(is, "Введите год поступления: ", 1900, 2100);
        month = readIntegerInput(is, "Введите месяц поступления (1-12): ", 1, 12);

        // Определяем максимальное количество дней в месяце
        const std::array<int, 12> daysInMonth = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int maxDays = daysInMonth[month - 1];

        // Корректировка для февраля
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                maxDays = 29; // Високосный год
            }
            else {
                maxDays = 28; // Невисокосный год
            }
        }

        day = readIntegerInput(is, "Введите день поступления: ", 1, maxDays);
    }
}

std::istream& operator>>(std::istream& is, Product& product) {
    std::string input;

    // Ввод наименования с проверкой
    while (true) {
        std::cout << "Введите наименование товара: ";
        if (std::getline(is, input)) {
            if (!input.empty()) {
                product.name = input;
                break;
            }
        }
        std::cout << "Ошибка: наименование не может быть пустым!\n";
    }

    // Ввод количества с проверкой
    product.quantity = readIntegerInput(is, "Введите количество: ", 0, 10000);

    // Ввод цены с проверкой
    product.price = readDoubleInput(is, "Введите цену: ", 0.0);

    // Ввод даты с проверкой
    int year, month, day;
    readDateInput(is, year, month, day);
    product.year = year;
    product.month = month;
    product.day = day;

    return is;
}

std::ifstream& operator>>(std::ifstream& ifs, Product& product) {
    std::string temp;

    if (!std::getline(ifs, product.name)) return ifs;
    if (!std::getline(ifs, temp)) return ifs;
    product.quantity = std::stoi(temp);
    if (!std::getline(ifs, temp)) return ifs;
    product.price = std::stod(temp);
    if (!std::getline(ifs, temp)) return ifs;
    product.year = std::stoi(temp);
    if (!std::getline(ifs, temp)) return ifs;
    product.month = std::stoi(temp);
    if (!std::getline(ifs, temp)) return ifs;
    product.day = std::stoi(temp);

    return ifs;
}