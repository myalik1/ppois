#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MultiSet;

/**
 * @brief Класс элемента мультимножества.
 * Может быть либо обычной строкой (атомом), либо содержать внутри другое мультимножество.
 */
class Element {
public:
    bool isSubSet;      ///< Флаг, указывающий, является ли элемент подмножеством.
    string atom;        ///< Значение элемента (если это обычная строка).
    MultiSet* subSet;   ///< Указатель на вложенное мультимножество (если isSubSet == true).

    /**
     * @brief Базовый конструктор.
     */
    Element();

    /**
     * @brief Создает атомарный элемент.
     * @param val Строковое значение элемента.
     */
    Element(const string val);

    /**
     * @brief Создает элемент-подмножество.
     * @param ms Мультимножество, которое нужно вложить.
     */
    Element(const MultiSet& ms);

    /**
     * @brief Конструктор копирования.
     * @param other Элемент для копирования.
     */
    Element(const Element& other);

    /**
     * @brief Оператор присваивания.
     * @param other Элемент для копирования.
     * @return Ссылка на текущий элемент.
     */
    Element& operator=(const Element& other);

    /**
     * @brief Деструктор, очищающий выделенную память под подмножество.
     */
    ~Element();

    /**
     * @brief Сравнивает два элемента на равенство.
     * @param other Элемент для сравнения.
     * @return true, если элементы равны.
     */
    bool operator==(Element& other);

    /**
     * @brief Сравнивает два элемента на неравенство.
     * @param other Элемент для сравнения.
     * @return true, если элементы не равны.
     */
    bool operator!=(Element& other);
};

/**
 * @brief Класс неориентированного мультимножества.
 * Хранит коллекцию элементов (атомов или других мультимножеств).
 */
class MultiSet{
public:
    /**
     * @brief Базовый конструктор пустого мультимножества.
     */
    MultiSet();

    /**
     * @brief Конструктор копирования.
     * @param other Мультимножество для копирования.
     */
    MultiSet(const MultiSet& other);

    /**
     * @brief Конструктор, создающий мультимножество из строки.
     * @param str Строка в формате "{a, {b, c}, a}".
     */
    MultiSet(string str);

    /**
     * @brief Оператор присваивания.
     * @param other Мультимножество для копирования.
     * @return Ссылка на текущее мультимножество.
     */
    MultiSet& operator=(const MultiSet& other);

    ~MultiSet();

    /**
     * @brief Добавляет строку как новый элемент.
     * @param val Строка для добавления.
     */
    void add(string val);

    /**
     * @brief Добавляет другое мультимножество как вложенный элемент.
     * @param ms Мультимножество для добавления.
     */
    void add(const MultiSet& ms);

    /**
     * @brief Добавляет готовый элемент.
     * @param el Элемент для добавления.
     */
    void add(const Element& el);

    /**
     * @brief Удаляет одно вхождение элемента.
     * @param el Элемент, который нужно удалить.
     * @return true, если элемент был найден и удален.
     */
    bool remove(Element& el);

    /**
     * @brief Считает количество вхождений конкретного элемента.
     * @param el Искомый элемент.
     * @return Количество найденных копий.
     */
    int count(Element& el);

    /**
     * @brief Возвращает количество элементов на верхнем уровне множества.
     * @return Размер множества.
     */
    int size();

    /**
     * @brief Проверяет, пустое ли множество.
     * @return true, если пусто.
     */
    bool empty();

    /**
     * @brief Полностью очищает мультимножество.
     */
    void clear();

    /**
     * @brief Выполняет сложение (объединение) двух мультимножеств.
     * @param other Второе мультимножество.
     * @return Новое мультимножество с результатом сложения.
     */
    MultiSet operator+(MultiSet& other);

    /**
     * @brief Выполняет вычитание (разность) двух мультимножеств.
     * @param other Второе мультимножество.
     * @return Новое мультимножество с результатом разности.
     */
    MultiSet operator-(MultiSet& other);

    /**
     * @brief Выполняет пересечение двух мультимножеств.
     * @param other Второе мультимножество.
     * @return Новое мультимножество с результатом пересечения.
     */
    MultiSet intersect(MultiSet other);

    /**
     * @brief Возвращает прямой доступ к вектору элементов.
     * @return Ссылка на внутренний вектор.
     */
    vector<Element>& getElements();

    /**
     * @brief Проверяет два мультимножества на полное совпадение.
     * @param other Множество для сравнения.
     * @return true, если множества равны.
     */
    bool operator==(MultiSet& other);

    /**
     * @brief Проверяет два мультимножества на неравенство.
     * @param other Множество для сравнения.
     * @return true, если множества не равны.
     */
    bool operator!=(MultiSet& other);

    /**
     * @brief Выводит мультимножество в поток вывода (например, cout).
     */
    friend ostream& operator<<(ostream& os, MultiSet& ms);

    /**
     * @brief Считывает мультимножество из потока ввода (например, cin).
     */
    friend istream& operator>>(istream& is, MultiSet& ms);
private:
    vector<Element> elements;
    void parse(string& str);
};
