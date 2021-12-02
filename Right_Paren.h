//
// Created by oblit on 9/13/2021.
//

#ifndef RIGHT_PAREN_H
#define RIGHT_PAREN_H
#include "Automaton.h"

class Right_Paren_Automaton : public Automaton
{
public:
    Right_Paren_Automaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
