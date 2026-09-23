#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MultiSet;

class Element {
public:
    bool isSubSet;
    string atom;
    MultiSet* subSet;

    Element();
    Element(const string val);
    Element(const MultiSet& ms);
    Element(const Element& other);
    Element& operator=(const Element& other);
    ~Element();

    bool operator==(Element& other);
    bool operator!=(Element& other);
};

class MultiSet{
public:
    MultiSet();
    MultiSet(const MultiSet& other);
    MultiSet(string str);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    void add(string val);
    void add(const MultiSet& ms);
    void add(const Element& el);
    bool remove(Element& el);

    int count(Element& el);
    int size();
    bool empty();
    void clear();

    MultiSet operator+(MultiSet& other);
    MultiSet operator-(MultiSet& other);
    MultiSet intersect(MultiSet& other);

    vector<Element>& getElements();
    bool operator==(MultiSet& other);
    bool operator!=(MultiSet& other);
    friend ostream& operator<<(ostream& os, MultiSet& ms);
    friend istream& operator>>(istream& is, MultiSet& ms);
private:
    vector<Element> elements;
    void parse(string& str);
};
