//
// Created by oblit on 9/13/2021.
//

#ifndef Q_MARK_H
#define Q_MARK_H
#include "Automaton.h"

class Q_Mark_Automaton : public Automaton
{
public:
    Q_Mark_Automaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
