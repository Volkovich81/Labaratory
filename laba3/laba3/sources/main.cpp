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
    // ������ ��� Windows
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    // ������������� ��������� ������
    setlocale(LC_ALL, "");
}

string inputString(string text) {
    string str;
    cout << text;
    getline(cin, str);
    return str;
}

// ��� ��������� ������� �������� ��� ���������
// [��������� ��� ����� ����� �� ��� � ���� ���]
int inputInt(string text, int min, int max) {
    int num;
    while (true) {
        cout << text;
        cin >> num;
        if (cin.fail() || num < min || num > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������! ������� ����� �� " << min << " �� " << max << endl;
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
            cout << "������! ������� ����� �� " << min << " �� " << max << endl;
        }
        else {
            cin.ignore(10000, '\n');
            return num;
        }
    }
}

string inputFuelType() {
    int choice;
    cout << "\n�������� ��� �������:" << endl;
    cout << "1. ������" << endl;
    cout << "2. ������" << endl;
    cout << "3. �������������" << endl;
    cout << "4. ���" << endl;

    choice = inputInt("��� ����� (1-4): ", 1, 4);

    switch (choice) {
    case 1: return "������";
    case 2: return "������";
    case 3: return "�������������";
    case 4: return "���";
    default: return "������";
    }
}

bool inputBool(string text) {
    int choice;
    cout << text << " (1 - ��, 0 - ���): ";
    choice = inputInt("", 0, 1);
    return choice == 1;
}

void showMenu() {
    cout << "\n==========================" << endl;
    cout << "   ������� ���������" << endl;
    cout << "==========================" << endl;
    cout << "1. �������� ���������" << endl;
    cout << "2. ���������� �������" << endl;
    cout << "3. �������� ���� ���������" << endl;
    cout << "4. �����" << endl;
    cout << "==========================" << endl;
}

void addTransport(Transport* transports[], int& count) {
    if (count >= MAX_TRANSPORTS) {
        cout << "��������� ����� ����������!" << endl;
        return;
    }

    cout << "\n�������� ��� ����������:" << endl;
    cout << "1. ����������" << endl;
    cout << "2. ���������" << endl;
    cout << "3. �������" << endl;

    int type = inputInt("��� �����: ", 1, 3);

    string name = inputString("��������: ");
    double speed = inputDouble("�������� (��/�): ", 1, 300);
    double cost = inputDouble("��������� �� ��: ", 0, 100);
    double weight = inputDouble("���������������� (��): ", 0, 10000);
    int people = inputInt("����������� ����������: ", 0, 100);

    switch (type) {
    case 1: {
        string fuel = inputFuelType();
        double use = inputDouble("������ ������� (�/100��): ", 0, 50);
        transports[count] = new Car(name, speed, cost, weight, people, fuel, use);
        count++;
        break;
    }
    case 2: {
        bool basket = inputBool("���� �������?");
        int gears = inputInt("���������� �������: ", 1, 30);
        transports[count] = new Bicycle(name, speed, cost, weight, people, basket, gears);
        count++;
        break;
    }
    case 3: {
        int horses = inputInt("���������� �������: ", 1, 10);
        bool covered = inputBool("������ �������?");
        transports[count] = new Carriage(name, speed, cost, weight, people, horses, covered);
        count++;
        break;
    }
    }
    cout << "��������� ��������!" << endl;
}

void calculateTrip(Transport* transports[], int count) {
    if (count == 0) {
        cout << "��� ����������!" << endl;
        return;
    }

    cout << "\n�������� ���������:" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << transports[i]->getName() << endl;
    }

    int choice = inputInt("��� �����: ", 1, count);
    Transport* transport = transports[choice - 1];

    double dist = inputDouble("���������� (��): ", 0.1, 10000);
    int people = inputInt("���������� ����������: ", 0, 100);
    double weight = inputDouble("��� ����� (��): ", 0, 10000);

    if (!transport->checkPeople(people)) {
        cout << "������� ����� ����������!" << endl;
        return;
    }

    if (!transport->checkWeight(weight)) {
        cout << "������� ������� ����!" << endl;
        return;
    }

    double time = transport->getTime(dist);
    double cost = transport->getCost(dist, people, weight);

    cout << fixed << setprecision(2);
    cout << "\n=== ���������� ===" << endl;
    cout << "�����: " << time << " �����" << endl;
    cout << "���������: " << cost << " ���." << endl;
    cout << "==================" << endl;
}

void showAllTransports(Transport* transports[], int count) {
    if (count == 0) {
        cout << "��� ����������!" << endl;
        return;
    }

    cout << "\n=== ���� ��������� ===" << endl;
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

    transports[transportCount++] = new Car("�����", 80, 2.5, 500, 4, "������", 8.5);
    transports[transportCount++] = new Bicycle("������", 15, 0.5, 20, 1, true, 21);
    transports[transportCount++] = new Carriage("������", 10, 1.5, 1000, 6, 2, true);

    int choice;
    do {
        showMenu();
        choice = inputInt("�������� ��������: ", 1, 4);

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
            cout << "�����..." << endl;
            break;
        }
    } while (choice != 4);

    for (int i = 0; i < transportCount; i++) {
        delete transports[i];
    }

    return 0;
}