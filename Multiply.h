//
// Created by oblit on 9/13/2021.
//

#ifndef MULTIPLY_H
#define MULTIPLY_H
#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
