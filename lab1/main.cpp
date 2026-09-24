#include <iostream>
#include <string>
#include <vector>
#include "MultiSet.h"
#include "PostMachine.h"

using namespace std;

void menuMultiSet() {
    cout << "\nНеориентированное мультимножество\n";
    cout << "Введите мультимножество в формате {a, {b, c}, a}: ";

    string input;
    getline(cin >> ws, input);

    MultiSet ms(input);
    cout << "Успешно считано: " << ms << "\n";
    cout << "Количество элементов: " << ms.size() << "\n";

    cout << "Введите атомарный элемент для добавления: ";
    string atom;
    getline(cin, atom);
    ms.add(atom);

    cout << "Результат после добавления: " << ms << "\n";
}

void menuPostMachine() {
    cout << "\n--- Машина Поста ---\n";
    PostMachine pm;

    vector<int> startTape = {0, 1, 2};
    pm.setTape(startTape);

    vector<string> myProgram = {
        "> 1",
        "0 2",
        "!"
    };
    pm.loadProgram(myProgram);

    cout << "Начальное состояние ленты:\n";
    pm.printState();

    cout << "Выполнение программы...\n";
    pm.run();

    cout << "Конечное состояние ленты:\n";
    pm.printState();
}

int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "\nГлавное меню:\n";
        cout << "1. Работать с классом MultiSet\n";
        cout << "2. Работать с классом PostMachine\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        switch (choice) {
            case 1:
                menuMultiSet();
                break;
            case 2:
                menuPostMachine();
                break;
            case 0:
                cout << "Завершение работы программы.\n";
                break;
            default:
                cout << "Неверный пункт меню.\n";
        }
    }

    return 0;
}
