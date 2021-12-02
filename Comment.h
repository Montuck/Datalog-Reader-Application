//
// Created by oblit on 9/14/2021.
//

#ifndef COMMENT_H
#define COMMENT_H
#include "Automaton.h"

class CommentAutomaton : public Automaton
{
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void SL(const std::string& input);
};

#endif