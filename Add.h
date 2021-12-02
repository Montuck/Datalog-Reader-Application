//
// Created by oblit on 9/13/2021.
//

#ifndef ADD_H
#define ADD_H
#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif