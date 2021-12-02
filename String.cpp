#include "String.h"
#include "Token.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead += 1;
        index += 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index == input.size()) {
        type = TokenType::UNDEFINED;
    }
    else if (input[index] != '\'') {
        if (input[index] == '\n') {
            newLines += 1;
        }
        inputRead += 1;
        index += 1;
        S1(input);
    }
    else if (input[index] == '\'') {
        inputRead += 1;
        index += 1;
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (index == input.size()) {}
    else if (input[index] == '\'') {
        inputRead += 1;
        index += 1;
        S1(input);
    }
}
