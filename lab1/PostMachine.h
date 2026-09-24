#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

/**
 * @brief Команда машины Поста.
 * Описывает одно действие, которое должна выполнить каретка.
 */
class Instruction {
public:
    char op;        ///< Тип операции: '>', '<', '1', '0', '?', '!'
    int nextLine;   ///< Номер строки, к которой нужно перейти дальше
    int altLine;    ///< Альтернативная строка перехода (используется только для '?')
};

/**
 * @brief Виртуальная машина Поста.
 * Управляет бесконечной лентой, кареткой и выполнением списка команд.
 */
class PostMachine {
public:
    /**
     * @brief Создает машину с кареткой на нулевой позиции.
     */
    PostMachine();

    /**
     * @brief Создает машину с кареткой на заданной позиции.
     * @param startHeadPosition Начальная позиция каретки.
     */
    explicit PostMachine(int startHeadPosition);

    /**
     * @brief Расставляет стартовые метки на ленте.
     * @param markedCells Список индексов ячеек, в которых нужно поставить метку '1'.
     */
    void setTape(vector<int>& markedCells);

    /**
     * @brief Добавляет одну команду в конец программы.
     * @param type Тип операции.
     * @param nextLine Следующая строка.
     * @param altLine Альтернативная строка (по умолчанию -1).
     */
    void addInstruction(char type, int nextLine, int altLine = -1);

    /**
     * @brief Запускает непрерывное выполнение программы до команды остановки '!'.
     */
    void run();

    /**
     * @brief Выполняет ровно один шаг программы.
     * @return true, если шаг выполнен успешно. false, если произошла остановка или ошибка.
     */
    bool step();

    /**
     * @brief Выводит в консоль текущее состояние ленты и положение каретки.
     */
    void printState();

    /**
     * @brief Загружает готовую программу из массива текстовых строк.
     * @param code Вектор строк с кодом программы.
     */
    void loadProgram(vector<string>& code);
private:
    int headPosition;
    int currentLine;
    unordered_map<int, bool> tape;
    vector<Instruction> program;
};
