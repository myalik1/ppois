#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "MultiSet.h"
#include "PostMachine.h"

using namespace std;

Element parseElement(string val) {
    size_t start = val.find_first_not_of(" \t");
    if (start != string::npos && val[start] == '{') {
        return Element(MultiSet(val));
    }
    return Element(val);
}

void menuMultiSet() {
    MultiSet ms;
    int choice = -1;

    while (choice != 0) {
        cout << "Меню Мультимножества\n";
        cout << "Текущее множество: " << ms << "\n";
        cout << "Размер: " << ms.size() << " | Пусто: " << (ms.empty() ? "Да" : "Нет") << "\n";
        cout << "1. Задать множество из строки (например: {a, {b}, a})\n";
        cout << "2. Добавить элемент\n";
        cout << "3. Удалить элемент\n";
        cout << "4. Узнать количество вхождений элемента\n";
        cout << "5. Очистить текущее множество\n";
        cout << "6. Объединить с другим множеством (+)\n";
        cout << "7. Вычесть другое множество (-)\n";
        cout << "8. Пересечь с другим множеством\n";
        cout << "9. Сравнить с другим множеством (==)\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            cout << "Введите строку: ";
            string input;
            getline(cin, input);
            ms = MultiSet(input);
        } else if (choice == 2) {
            cout << "Введите значение для добавления: ";
            string val;
            getline(cin, val);
            ms.add(parseElement(val));
        } else if (choice == 3) {
            cout << "Введите значение для удаления: ";
            string val;
            getline(cin, val);
            Element el = parseElement(val);
            if (ms.remove(el)) cout << "Элемент удален.\n";
            else cout << "Элемент не найден.\n";
        } else if (choice == 4) {
            cout << "Введите искомый элемент: ";
            string val;
            getline(cin, val);
            Element el = parseElement(val);
            cout << "Количество: " << ms.count(el) << "\n";
        } else if (choice == 5) {
            ms.clear();
            cout << "Множество очищено.\n";
        } else if (choice >= 6 && choice <= 8) {
            cout << "Введите второе множество (например: {a, b}): ";
            string input;
            getline(cin, input);
            MultiSet other(input);
            MultiSet result;

            if (choice == 6) {
                result = ms + other;
                cout << "Результат объединения: " << result << "\n";
            } else if (choice == 7) {
                result = ms - other;
                cout << "Результат разности: " << result << "\n";
            } else if (choice == 8) {
                result = ms.intersect(other);
                cout << "Результат пересечения: " << result << "\n";
            }

            cout << "Заменить текущее множество результатом? (1 - да, 0 - нет): ";
            int saveChoice;
            if (cin >> saveChoice && saveChoice == 1) {
                ms = result;
                cout << "Текущее множество обновлено.\n";
            }
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (choice == 9) {
            cout << "Введите второе множество для сравнения: ";
            string input;
            getline(cin, input);
            MultiSet other(input);
            if (ms == other) {
                cout << "Результат: Множества РАВНЫ.\n";
            } else {
                cout << "Результат: Множества НЕ РАВНЫ.\n";
            }
        }
    }
}

void menuPostMachine() {
    PostMachine pm;
    int choice = -1;

    while (choice != 0) {
        cout << "Меню Машины Поста\n";
        pm.printState();
        cout << "1. Установить метки на ленте (ввести индексы через пробел)\n";
        cout << "2. Добавить команду в программу\n";
        cout << "3. Загрузить тестовую программу (шаг вправо, стереть, стоп)\n";
        cout << "4. Выполнить один шаг (step)\n";
        cout << "5. Запустить до конца (run)\n";
        cout << "6. Вернуть каретку на строку 0 (reset)\n";
        cout << "7. Очистить текущую программу\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            cout << "Введите индексы через пробел: ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            vector<int> cells;
            int pos;
            while (iss >> pos) cells.push_back(pos);
            pm.setTape(cells);
        } else if (choice == 2) {
            cout << "Введите команду (тип следующая_строка [альт_строка]). Пример '? 2 3' или '> 1': ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            char op;
            int nextL = -1, altL = -1;
            iss >> op;
            if (op != '!') iss >> nextL;
            if (op == '?') iss >> altL;
            pm.addInstruction(op, nextL, altL);
            cout << "Команда добавлена.\n";
        } else if (choice == 3) {
            vector<string> prog = {"> 1", "0 2", "!"};
            pm.loadProgram(prog);
            cout << "Тестовая программа загружена.\n";
        } else if (choice == 4) {
            if (pm.step()) cout << "Шаг выполнен.\n";
            else cout << "Программа остановлена или достигла конца.\n";
        } else if (choice == 5) {
            pm.run();
            cout << "Выполнение завершено.\n";
        } else if (choice == 6) {
            pm.reset();
            cout << "Каретка возвращена на старт.\n";
        } else if (choice == 7) {
            pm.clearProgram();
            cout << "Программа полностью очищена.\n";
        }
    }
}

int main() {
    int choice = -1;
    while (choice != 0) {
        cout << "ГЛАВНОЕ МЕНЮ\n";
        cout << "1. Работа с Мультимножеством\n";
        cout << "2. Работа с Машиной Поста\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        if (choice == 1) {
            menuMultiSet();
        } else if (choice == 2) {
            menuPostMachine();
        } else if (choice == 0) {
            cout << "Завершение программы.\n";
        } else {
            cout << "Неверный пункт меню.\n";
        }
    }
    return 0;
}
