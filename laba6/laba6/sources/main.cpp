#include <iostream>
#include <string>
#include <iomanip>
#include <array>
#include <vector>
#include <limits>
#include <cctype>
#define NOMINMAX  
#include <windows.h>
#include "../headers/transport.h"
#include "../headers/car.h"
#include "../headers/carriage.h"
#include "../headers/bicycle.h"
#include "../headers/validation_exception.h"

using namespace std;

const int MAX_TRANSPORTS = 50;

void setRussianLocale() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidString(const std::string& str) {
    for (char c : str) {
        if (!(isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return false;
        }
    }
    return true;
}

string inputString(const string& text) {
    string str;
    while (true) {
        cout << text;
        getline(cin, str);

        try {
            if (!isValidString(str)) {
                throw ValidationException("Ошибка! Введена недопустимая информация. Разрешены только цифры, строчные и прописные латинские символы.");
            }
            break;
        }
        catch (const ValidationException& e) {
            cout << e.what() << endl;
            cout << "Пожалуйста, введите строку заново: ";
        }
    }
    return str;
}

int inputInt(const string& text, int min, int max) {
    int num;
    while (true) {
        cout << text;
        cin >> num;
        if (cin.fail() || num < min || num > max) {
            cin.clear();
            clearInputBuffer();
            cout << "Ошибка! Введите число от " << min << " до " << max << endl;
        }
        else {
            clearInputBuffer();
            return num;
        }
    }
}

double inputDouble(const string& text, double min, double max) {
    double num;
    while (true) {
        cout << text;
        cin >> num;
        if (cin.fail() || num < min || num > max) {
            cin.clear();
            clearInputBuffer();
            cout << "Ошибка! Введите число от " << min << " до " << max << endl;
        }
        else {
            clearInputBuffer();
            return num;
        }
    }
}

string inputFuelType() {
    int choice;
    cout << "\nВыберите тип топлива:" << endl;
    cout << "1. Бензин" << endl;
    cout << "2. Дизель" << endl;
    cout << "3. Электричество" << endl;
    cout << "4. Газ" << endl;

    choice = inputInt("Ваш выбор (1-4): ", 1, 4);

    switch (choice) {
    case 1: return "Бензин";
    case 2: return "Дизель";
    case 3: return "Электричество";
    case 4: return "Газ";
    default: return "Бензин";
    }
}

bool inputBool(const string& text) {
    int choice;
    cout << text << " (1 - да, 0 - нет): ";
    choice = inputInt("", 0, 1);
    return choice == 1;
}

void showMenu() {
    cout << "\n==========================" << endl;
    cout << "   СИСТЕМА ПЕРЕВОЗОК" << endl;
    cout << "==========================" << endl;
    cout << "1. Добавить транспорт" << endl;
    cout << "2. Рассчитать поездку" << endl;
    cout << "3. Показать весь транспорт" << endl;
    cout << "4. Демонстрация исключений" << endl;
    cout << "5. Выход" << endl;
    cout << "==========================" << endl;
}

void addTransport(array<Transport*, MAX_TRANSPORTS>& transports, int& count) {
    if (count >= MAX_TRANSPORTS) {
        cout << "Достигнут лимит транспорта!" << endl;
        return;
    }

    cout << "\nВыберите тип транспорта:" << endl;
    cout << "1. Автомобиль" << endl;
    cout << "2. Велосипед" << endl;
    cout << "3. Повозка" << endl;

    int type = inputInt("Ваш выбор: ", 1, 3);

    try {
        string name = inputString("Название: ");
        double speed = inputDouble("Скорость (км/ч): ", 1, 300);
        double cost = inputDouble("Стоимость за км: ", 0, 100);
        double weight = inputDouble("Грузоподъемность (кг): ", 0, 10000);
        int people = inputInt("Вместимость пассажиров: ", 0, 100);

        switch (type) {
        case 1: {
            string fuel = inputFuelType();
            double use = inputDouble("Расход топлива (л/100км): ", 0, 50);
            transports[count] = new Car(name, speed, cost, weight, people, fuel, use);
            count++;
            cout << "Автомобиль '" << name << "' добавлен!" << endl;
            break;
        }
        case 2: {
            bool basket = inputBool("Есть корзина?");
            int gears = inputInt("Количество передач: ", 1, 30);
            transports[count] = new Bicycle(name, speed, cost, weight, people, basket, gears);
            count++;
            cout << "Велосипед '" << name << "' добавлен!" << endl;
            break;
        }
        case 3: {
            int horses = inputInt("Количество лошадей: ", 1, 10);
            bool covered = inputBool("Крытая повозка?");
            transports[count] = new Carriage(name, speed, cost, weight, people, horses, covered);
            count++;
            cout << "Повозка '" << name << "' добавлена!" << endl;
            break;
        }
        }
    }
    catch (const ValidationException& e) {
        cout << "Ошибка при создании транспорта: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Произошла ошибка: " << e.what() << endl;
    }
}

void calculateTrip(array<Transport*, MAX_TRANSPORTS>& transports, int count) {
    if (count == 0) {
        cout << "Нет транспорта!" << endl;
        return;
    }

    cout << "\nВыберите транспорт:" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << transports[i]->getName() << endl;
    }

    int choice = inputInt("Ваш выбор: ", 1, count);
    Transport* transport = transports[choice - 1];

    double dist = inputDouble("Расстояние (км): ", 0.1, 10000);

    int people;
    do {
        people = inputInt("Количество пассажиров: ", 0, 100);
        if (!transport->checkPeople(people)) {
            cout << "Слишком много пассажиров! Максимум: " << transport->getMaxPeople() << endl;
        }
    } while (!transport->checkPeople(people));

    double weight;
    do {
        weight = inputDouble("Вес груза (кг): ", 0, 10000);
        if (!transport->checkWeight(weight)) {
            cout << "Слишком тяжелый груз! Максимум: " << transport->getMaxWeight() << " кг" << endl;
        }
    } while (!transport->checkWeight(weight));

    double time = transport->getTime(dist);
    double cost = transport->getCost(dist, people, weight);

    cout << fixed << setprecision(2);
    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "Время: " << time << " часов" << endl;
    cout << "Стоимость: " << cost << " руб." << endl;
    cout << "==================" << endl;
}

void showAllTransports(array<Transport*, MAX_TRANSPORTS>& transports, int count) {
    if (count == 0) {
        cout << "Нет транспорта!" << endl;
        return;
    }

    cout << "\n=== ВЕСЬ ТРАНСПОРТ ===" << endl;
    for (int i = 0; i < count; i++) {
        transports[i]->showInfo();
        if (i < count - 1) {
            cout << "----------------------" << endl;
        }
    }
    cout << "======================" << endl;
}

void demonstrateExceptions() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ИСКЛЮЧЕНИЙ ===" << endl;

    vector<string> testCases = {
        "ValidName123",
        "Invalid Name",
        "РусскоеИмя",
        "name-with-dash",
        "AnotherValid"
    };

    for (const auto& testCase : testCases) {
        cout << "\nТестируем: '" << testCase << "'" << endl;
        try {
            if (!isValidString(testCase)) {
                throw ValidationException("Обнаружены недопустимые символы в строке: '" + testCase + "'");
            }
            cout << "✓ Валидация пройдена успешно!" << endl;
        }
        catch (const ValidationException& e) {
            cout << "✗ " << e.what() << endl;
        }
    }
    cout << "=================================" << endl;
}

int main() {
    setRussianLocale();

    array<Transport*, MAX_TRANSPORTS> transports{};
    int transportCount = 0;

    try {
        transports[transportCount] = new Car("FamilySedan123", 80, 2.5, 500, 4, "Бензин", 8.5);
        transportCount++;

        transports[transportCount] = new Bicycle("MountainBike21", 15, 0.5, 20, 1, true, 21);
        transportCount++;

        transports[transportCount] = new Carriage("RoyalCarriage2", 10, 1.5, 1000, 6, 2, true);
        transportCount++;
    }
    catch (const ValidationException& e) {
        cout << "Ошибка при создании тестового транспорта: " << e.what() << endl;
    }

    int choice;
    do {
        showMenu();
        choice = inputInt("Выберите действие: ", 1, 5);

        switch (choice) {
        case 1:
            addTransport(transports, transportCount);
            break;
        case 2:
            calculateTrip(transports, transportCount);
            break;
        case 3:
            showAllTransports(transports, transportCount);
            break;
        case 4:
            demonstrateExceptions();
            break;
        case 5:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    } while (choice != 5);

    for (int i = 0; i < transportCount; i++) {
        delete transports[i];
    }

    return 0;
}