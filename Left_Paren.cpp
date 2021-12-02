#include "Left_Paren.h"

void Left_Paren_Automaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

