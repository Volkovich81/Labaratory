#include "../headers/menu.h"
#include "../headers/utils.h"
#include <iostream>

int main()
{
    system("cls");
    int choice;

    do
    {
        showMenu();
        choice = getInput<int>("");

        switch (choice)
        {
        case 1:
            handleArrayMenu<int>("int");
            break;
        case 2:
            handleArrayMenu<double>("double");
            break;
        case 3:
            handleArrayMenu<char>("char");
            break;
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}