#include "PostMachine.h"


PostMachine::PostMachine() {
    headPosition = 0;
    currentLine = 0;
}

PostMachine::PostMachine(int startHeadPosition) {
    headPosition = startHeadPosition;
    currentLine = 0;
}

void PostMachine::setTape(vector<int>& markedCells) {
    tape.clear();
    for (int cell : markedCells) {
        tape[cell] = true;
    }
}

void PostMachine::addInstruction(char type, int nextLine, int altLine) {
    Instruction instr;
    instr.op = type;
    instr.nextLine = nextLine;
    instr.altLine = altLine;
    program.push_back(instr);
}

bool PostMachine::step() {
    if (currentLine < 0 || currentLine >= program.size()) {
        return false;
    }
    Instruction instr = program[currentLine];

    switch (instr.op) {
            case '>':
                headPosition++;
                currentLine = instr.nextLine;
                break;
            case '<':
                headPosition--;
                currentLine = instr.nextLine;
                break;
            case '1':
                tape[headPosition] = true;
                currentLine = instr.nextLine;
                break;
            case '0':
                tape[headPosition] = false;
                currentLine = instr.nextLine;
                break;
            case '?':
                if (tape[headPosition]) {
                    currentLine = instr.altLine;
                } else {
                    currentLine = instr.nextLine;
                }
                break;
            case '!':
                return false;
            default:
                return false;
        }
        return true;
}

void PostMachine::run() {
    while(step()){}
}

void PostMachine::printState() {
    cout << "Tape: ";
    for (int i = headPosition - 5; i <= headPosition + 5; i++) {
        if (tape[i]) {
            cout << "[1]";
        } else {
            cout << "[0]";
        }
    }
    cout << "\n       ";

    for (int i = headPosition - 5; i < headPosition; i++) {
        cout << "   ";
    }
    cout << " ^\n";
}

void PostMachine::loadProgram(vector<string>& code) {
    program.clear();

    for (string& line : code) {
        istringstream iss(line);
        char type;
        int nextLine = 0;
        int altLine = -1;

        iss >> type;

        if (type != '!') {
            iss >> nextLine;

            if (type == '?') {
                iss >> altLine;
            }
        }

        addInstruction(type, nextLine, altLine);
    }
}
