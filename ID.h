//
// Created by oblit on 9/14/2021.
//

#ifndef ID_H
#define ID_H
#include "Automaton.h"

class IDAutomaton : public Automaton
{
public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
};

#endif