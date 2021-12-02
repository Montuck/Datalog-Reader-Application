//
// Created by oblit on 9/13/2021.
//

#ifndef PERIOD_H
#define PERIOD_H
#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
