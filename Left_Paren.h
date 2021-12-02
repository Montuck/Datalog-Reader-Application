//
// Created by oblit on 9/13/2021.
//

#ifndef LEFT_PAREN_H
#define LEFT_PAREN_H
#include "Automaton.h"

class Left_Paren_Automaton : public Automaton
{
public:
    Left_Paren_Automaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
