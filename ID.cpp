#include "ID.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead += 1;
        index += 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if(index == input.size()) {
        Serr();
    }
    else if(isspace(input[index])) {
        //do nothing
    }
    else if (isalnum(input[index])) {
        inputRead += 1;
        index += 1;
        S1(input);
    }
}
