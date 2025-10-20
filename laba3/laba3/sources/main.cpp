#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include "transport.h"
#include "car.h"
#include "bicycle.h"
#include "carriage.h"

using namespace std;

const int MAX_TRANSPORTS = 50;

void setRussianLocale() {
    // Только для Windows
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    // Универсальная установка локали
    setlocale(LC_ALL, "");
}

string inputString(string text) {
    string str;
    cout << text;
    getline(cin, str);
    return str;
}

// Все остальные функции остаются БЕЗ ИЗМЕНЕНИЙ
// [остальной код точно такой же как у тебя был]
int inputInt(string text, int min, int max) {
    int num;
    while (true) {
        cout << text;
        cin >> num;
        if (cin.fail() || num < min || num > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от " << min << " до " << max << endl;
        }
        else {
            cin.ignore(10000, '\n');
            return num;
        }
    }
}

double inputDouble(string text, double min, double max) {
    double num;
    while (true) {
        cout << text;
        cin >> num;
        if (cin.fail() || num < min || num > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от " << min << " до " << max << endl;
        }
        else {
            cin.ignore(10000, '\n');
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

bool inputBool(string text) {
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
    cout << "4. Выход" << endl;
    cout << "==========================" << endl;
}

void addTransport(Transport* transports[], int& count) {
    if (count >= MAX_TRANSPORTS) {
        cout << "Достигнут лимит транспорта!" << endl;
        return;
    }

    cout << "\nВыберите тип транспорта:" << endl;
    cout << "1. Автомобиль" << endl;
    cout << "2. Велосипед" << endl;
    cout << "3. Повозка" << endl;

    int type = inputInt("Ваш выбор: ", 1, 3);

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
        break;
    }
    case 2: {
        bool basket = inputBool("Есть корзина?");
        int gears = inputInt("Количество передач: ", 1, 30);
        transports[count] = new Bicycle(name, speed, cost, weight, people, basket, gears);
        count++;
        break;
    }
    case 3: {
        int horses = inputInt("Количество лошадей: ", 1, 10);
        bool covered = inputBool("Крытая повозка?");
        transports[count] = new Carriage(name, speed, cost, weight, people, horses, covered);
        count++;
        break;
    }
    }
    cout << "Транспорт добавлен!" << endl;
}

void calculateTrip(Transport* transports[], int count) {
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
    int people = inputInt("Количество пассажиров: ", 0, 100);
    double weight = inputDouble("Вес груза (кг): ", 0, 10000);

    if (!transport->checkPeople(people)) {
        cout << "Слишком много пассажиров!" << endl;
        return;
    }

    if (!transport->checkWeight(weight)) {
        cout << "Слишком тяжелый груз!" << endl;
        return;
    }

    double time = transport->getTime(dist);
    double cost = transport->getCost(dist, people, weight);

    cout << fixed << setprecision(2);
    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "Время: " << time << " часов" << endl;
    cout << "Стоимость: " << cost << " руб." << endl;
    cout << "==================" << endl;
}

void showAllTransports(Transport* transports[], int count) {
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

int main() {
    setRussianLocale();

    Transport* transports[MAX_TRANSPORTS];
    int transportCount = 0;

    transports[transportCount++] = new Car("Седан", 80, 2.5, 500, 4, "Бензин", 8.5);
    transports[transportCount++] = new Bicycle("Горный", 15, 0.5, 20, 1, true, 21);
    transports[transportCount++] = new Carriage("Карета", 10, 1.5, 1000, 6, 2, true);

    int choice;
    do {
        showMenu();
        choice = inputInt("Выберите действие: ", 1, 4);

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
            cout << "Выход..." << endl;
            break;
        }
    } while (choice != 4);

    for (int i = 0; i < transportCount; i++) {
        delete transports[i];
    }

    return 0;
}