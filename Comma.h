//
// Created by oblit on 9/13/2021.
//

#ifndef COMMA_H
#define COMMA_H
#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
