#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

class Instruction {
public:
    char op;
    int nextLine;
    int altLine;
};

class PostMachine {
public:
    PostMachine();
    explicit PostMachine(int startHeadPosition);
    void setTape(vector<int>& markedCells);
    void addInstruction(char type, int nextLine, int altLine = -1);
    void run();
    bool step();
    void printState();
    void loadProgram(vector<string>& code);
private:
    int headPosition;
    int currentLine;
    unordered_map<int, bool> tape;
    vector<Instruction> program;
};
