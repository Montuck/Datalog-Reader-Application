#include "Queries.h"

void QueriesAutomaton::S0(const std::string& input) {
    if (input[index] == 'Q') {
        inputRead += 1;
        index += 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        inputRead += 1;
        index += 1;
        S2(input);
    }
    else {
        Serr();
    }
}
void QueriesAutomaton::S2(const std::string& input) {
    if (input[index] == 'e') {
        inputRead += 1;
        index += 1;
        S3(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S3(const std::string& input) {
    if (input[index] == 'r') {
        inputRead += 1;
        index += 1;
        S4(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S4(const std::string& input) {
    if (input[index] == 'i') {
        inputRead += 1;
        index += 1;
        S5(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        inputRead += 1;
        index += 1;
        S6(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead += 1;
        index += 1;
    }
    else {
        Serr();
    }
}