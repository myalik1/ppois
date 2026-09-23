#include "MultiSet.h"

string trim(string s) {
    while (!s.empty() && isspace(s.front())) s.erase(s.begin());
    while (!s.empty() && isspace(s.back())) s.pop_back();
    return s;
}

Element::Element() : isSubSet(false), atom(""), subSet(nullptr) {}

Element::Element(const string val) : isSubSet(false), atom(val), subSet(nullptr) {}

Element::Element(const MultiSet& ms) : isSubSet(true), atom(""), subSet(new MultiSet(ms)) {}

Element::Element(const Element& other) {
    isSubSet = other.isSubSet;
    atom = other.atom;
    subSet = other.subSet ? new MultiSet(*other.subSet) : nullptr;
}

Element& Element::operator=(const Element& other) {
    if (this != &other) {
        delete subSet;
        isSubSet = other.isSubSet;
        atom = other.atom;
        subSet = other.subSet ? new MultiSet(*other.subSet) : nullptr;
    }
    return *this;
}

Element::~Element() {
    delete subSet;
}

bool Element::operator==(Element& other) {
    if (isSubSet != other.isSubSet) return false;
    if (!isSubSet) return atom == other.atom;
    return *subSet == *other.subSet;
}

bool Element::operator!=(Element& other){
    return !(*this == other);
}

MultiSet::MultiSet() {}

MultiSet::MultiSet(string str) {
    parse(str);
}

MultiSet::MultiSet(const MultiSet& other) : elements(other.elements) {}

MultiSet& MultiSet::operator=(const MultiSet& other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}

MultiSet::~MultiSet() {}

void MultiSet::add(string val) {
    elements.push_back(Element(val));
}

void MultiSet::add(const MultiSet& ms) {
    elements.push_back(Element(ms));
}

void MultiSet::add(const Element& el) {
    elements.push_back(el);
}

bool MultiSet::remove(Element& el) {
    for (auto it = elements.begin(); it != elements.end(); it++) {
        if (*it == el) {
            elements.erase(it);
            return true;
        }
    }
    return false;
}

int MultiSet::count(Element& el) {
    int total = 0;
    for (auto& item : elements) {
        if (item == el) total++;
    }
    return total;
}

int MultiSet::size() {
    return elements.size();
}

bool MultiSet::empty() {
    return elements.empty();
}

void MultiSet::clear() {
    elements.clear();
}

MultiSet MultiSet::operator+(MultiSet& other) {
    MultiSet result(*this);
    for (auto& el : other.elements) {
        result.add(el);
    }
    return result;
}

MultiSet MultiSet::operator-(MultiSet& other) {
    MultiSet result(*this);
    for (auto& el : other.elements) {
        result.remove(el);
    }
    return result;
}

MultiSet MultiSet::intersect(MultiSet& other) {
    MultiSet result;
    for (auto& el : elements) {
        if (other.count(el) > 0) {
            result.add(el);
        }
    }
    return result;
}

vector<Element>& MultiSet::getElements() {
    return elements;
}

bool MultiSet::operator==(MultiSet& other) {
    if (size() != other.size()) return false;
    for (auto& el : elements) {
        if (count(el) != other.count(el)) return false;
    }
    return true;
}

bool MultiSet::operator!=(MultiSet& other) {
    return !(*this == other);
}

void MultiSet::parse(string& str) {
    elements.clear();

    size_t first = str.find('{');
    size_t last = str.rfind('}');
    if (first == string::npos || last == string::npos || first >= last) return;

    string content = str.substr(first + 1, last - first - 1);
    string token = "";
    int depth = 0;

    for (char c : content) {
        if (c == '{') depth++;
        if (c == '}') depth--;

        if (c == ',' && depth == 0) {
            token = trim(token);
            if (!token.empty()) {
                if (token.front() == '{') add(MultiSet(token));
                else add(token);
            }
            token = "";
        } else {
            token += c;
        }
    }

    token = trim(token);
    if (!token.empty()) {
        if (token.front() == '{') add(MultiSet(token));
        else add(token);
    }
}

ostream& operator<<(ostream& os, MultiSet& ms) {
    os << "{";
    for (size_t i = 0; i < ms.elements.size(); i++) {
        if (ms.elements[i].isSubSet) {
            os << *ms.elements[i].subSet;
        } else {
            os << ms.elements[i].atom;
        }
        if (i + 1 < ms.elements.size()) os << ", ";
    }
    os << "}";
    return os;
}

istream& operator>>(istream& is, MultiSet& ms) {
    string line;
    if (getline(is, line)) {
        ms.parse(line);
    }
    return is;
}
