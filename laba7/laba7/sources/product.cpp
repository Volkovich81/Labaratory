#include "../headers/product.h"
#include <limits>
#include <stdexcept>
#include <cstring>
#include <sstream>
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

// Вспомогательная функция для проверки, является ли строка целым числом
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

// Вспомогательная функция для проверки, является ли строка числом (целым или дробным)
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

std::istream& operator>>(std::istream& is, Product& product) {
    std::string input;

    // Ввод наименования
    while (true) {
        std::cout << "Введите наименование товара: ";
        if (std::getline(is, input) && !input.empty()) {
            product.name = input;
            break;
        }
        std::cout << "Ошибка: наименование не может быть пустым!\n";
    }

    // Ввод количества
    while (true) {
        std::cout << "Введите количество: ";
        if (std::getline(is, input) && isInteger(input)) {
            try {
                int q = std::stoi(input);
                if (product.setQuantity(q)) {
                    break;
                }
                std::cout << "Ошибка: количество не может быть отрицательным!\n";
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

    // Ввод цены
    while (true) {
        std::cout << "Введите цену: ";
        if (std::getline(is, input)) {
            for (char& c : input) {
                if (c == ',') c = '.';
            }

            if (isNumber(input)) {
                try {
                    double p = std::stod(input);
                    if (product.setPrice(p)) {
                        break;
                    }
                    std::cout << "Ошибка: цена не может быть отрицательной!\n";
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

    // Ввод даты
    int y = 0;
    int m = 0;
    int d = 0;

    // Ввод года
    while (true) {
        std::cout << "Введите год поступления: ";
        if (!std::getline(is, input) || !isInteger(input)) {
            std::cout << "Ошибка: год должен быть целым числом!\n";
            continue;
        }

        try {
            y = std::stoi(input);
            if (y >= 1900 && y <= 2100) break;
            std::cout << "Ошибка: год должен быть в диапазоне 1900-2100!\n";
        }
        catch (const std::invalid_argument&) {
            std::cout << "Ошибка: введите корректный год!\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Ошибка: год слишком большой!\n";
        }
    }

    // Ввод месяца
    while (true) {
        std::cout << "Введите месяц поступления (1-12): ";
        if (!std::getline(is, input) || !isInteger(input)) {
            std::cout << "Ошибка: месяц должен быть целым числом!\n";
            continue;
        }

        try {
            m = std::stoi(input);
            if (m >= 1 && m <= 12) break;
            std::cout << "Ошибка: месяц должен быть в диапазоне 1-12!\n";
        }
        catch (const std::invalid_argument&) {
            std::cout << "Ошибка: введите корректный месяц!\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Ошибка: месяц слишком большой!\n";
        }
    }

    // Ввод дня
    while (true) {
        std::cout << "Введите день поступления: ";
        if (!std::getline(is, input) || !isInteger(input)) {
            std::cout << "Ошибка: день должен быть целым числом!\n";
            continue;
        }

        try {
            d = std::stoi(input);
            if (d < 1 || d > 31) {
                std::cout << "Ошибка: день должен быть в диапазоне 1-31!\n";
                continue;
            }

            const std::array<int, 12> daysInMonth = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            int maxDays = daysInMonth[m - 1];

            if (m == 2) {
                if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
                    maxDays = 29;
                }
                else {
                    maxDays = 28;
                }
            }

            if (d <= maxDays) break;
            std::cout << "Ошибка: в " << m << " месяце не может быть " << d << " дней! Максимум: " << maxDays << " дней.\n";
        }
        catch (const std::invalid_argument&) {
            std::cout << "Ошибка: введите корректный день!\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Ошибка: день слишком большой!\n";
        }
    }

    if (!product.setDate(y, m, d)) {
        std::cout << "Ошибка: некорректная дата! Проверьте введенные значения.\n";
    }

    return is;
}