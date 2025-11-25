#include "../headers/product.h"
#include <limits>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <cctype>

Product::Product() : name(""), quantity(0), price(0.0), year(2000), month(1), day(1) {}

Product::Product(const std::string& n, int q, double p, int y, int m, int d) :
    name(n), quantity(q), price(p), year(y), month(m), day(d) {
}

bool Product::isValidDate(int y, int m, int d) const {
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;

    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
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

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << product.name << " " << product.quantity << " " << product.price
        << " " << product.year << " " << product.month << " " << product.day;
    return os;
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
            if (hasDecimalPoint) return false; // Две точки
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
        if (std::getline(is, input)) {
            if (!input.empty()) {
                product.name = input;
                break;
            }
        }
        std::cout << "Ошибка: наименование не может быть пустым!\n";
    }

    // Ввод количества
    while (true) {
        std::cout << "Введите количество: ";
        if (std::getline(is, input)) {
            if (isInteger(input)) {
                try {
                    int q = std::stoi(input);
                    if (product.setQuantity(q)) {
                        break;
                    }
                    else {
                        std::cout << "Ошибка: количество не может быть отрицательным!\n";
                    }
                }
                catch (const std::exception&) {
                    std::cout << "Ошибка: введите корректное целое число!\n";
                }
            }
            else {
                std::cout << "Ошибка: введите целое число!\n";
            }
        }
    }

    // Ввод цены
    while (true) {
        std::cout << "Введите цену: ";
        if (std::getline(is, input)) {
            // Заменяем запятую на точку для корректного ввода
            for (char& c : input) {
                if (c == ',') c = '.';
            }

            if (isNumber(input)) {
                try {
                    double p = std::stod(input);
                    if (product.setPrice(p)) {
                        break;
                    }
                    else {
                        std::cout << "Ошибка: цена не может быть отрицательной!\n";
                    }
                }
                catch (const std::exception&) {
                    std::cout << "Ошибка: введите корректное число!\n";
                }
            }
            else {
                std::cout << "Ошибка: введите число (можно использовать точку или запятую)!\n";
            }
        }
    }

    // Ввод даты
    while (true) {
        int y = 0, m = 0, d = 0;

        // Ввод года
        while (true) {
            std::cout << "Введите год поступления: ";
            if (!std::getline(is, input)) continue;

            if (!isInteger(input)) {
                std::cout << "Ошибка: год должен быть целым числом!\n";
                continue;
            }

            try {
                y = std::stoi(input);
                if (y < 1900 || y > 2100) {
                    std::cout << "Ошибка: год должен быть в диапазоне 1900-2100!\n";
                    continue;
                }
                break;
            }
            catch (const std::exception&) {
                std::cout << "Ошибка: введите корректный год!\n";
            }
        }

        // Ввод месяца
        while (true) {
            std::cout << "Введите месяц поступления (1-12): ";
            if (!std::getline(is, input)) continue;

            if (!isInteger(input)) {
                std::cout << "Ошибка: месяц должен быть целым числом!\n";
                continue;
            }

            try {
                m = std::stoi(input);
                if (m < 1 || m > 12) {
                    std::cout << "Ошибка: месяц должен быть в диапазоне 1-12!\n";
                    continue;
                }
                break;
            }
            catch (const std::exception&) {
                std::cout << "Ошибка: введите корректный месяц!\n";
            }
        }

        // Ввод дня
        while (true) {
            std::cout << "Введите день поступления: ";
            if (!std::getline(is, input)) continue;

            if (!isInteger(input)) {
                std::cout << "Ошибка: день должен быть целым числом!\n";
                continue;
            }

            try {
                d = std::stoi(input);

                // Предварительная проверка диапазона дней
                if (d < 1 || d > 31) {
                    std::cout << "Ошибка: день должен быть в диапазоне 1-31!\n";
                    continue;
                }

                // Более точная проверка для каждого месяца
                const int daysInMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                int maxDays = daysInMonth[m - 1];

                // Корректировка для февраля в високосный год
                if (m == 2) {
                    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
                        maxDays = 29;
                    }
                    else {
                        maxDays = 28;
                    }
                }

                if (d > maxDays) {
                    std::cout << "Ошибка: в " << m << " месяце не может быть " << d << " дней! Максимум: " << maxDays << " дней.\n";
                    continue;
                }

                break;
            }
            catch (const std::exception&) {
                std::cout << "Ошибка: введите корректный день!\n";
            }
        }

        // Финальная проверка всей даты
        if (product.setDate(y, m, d)) {
            break;
        }
        else {
            std::cout << "Ошибка: некорректная дата! Проверьте введенные значения.\n";
        }
    }

    return is;
}

std::ofstream& operator<<(std::ofstream& ofs, const Product& product) {
    ofs << product.name << "\n" << product.quantity << "\n" << product.price << "\n"
        << product.year << "\n" << product.month << "\n" << product.day << "\n";
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Product& product) {
    std::string temp;

    if (!std::getline(ifs, product.name)) {
        return ifs;
    }

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