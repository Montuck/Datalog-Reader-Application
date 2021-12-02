#include "Comment.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead += 1;
        index += 1;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead += 1;
        index += 1;
        S2(input);
    }
    if (input[index] != '\n' && index != input.size()) {
        inputRead += 1;
        index += 1;
        SL(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::SL(const std::string& input) {
    if (input[index] != '\n' && index != input.size()) {
        inputRead += 1;
        index += 1;
        SL(input);
    }
    else if (input[index] == '\n' || index == input.size()) {
        //do nothing
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if (index == input.size()) {
        type = TokenType::UNDEFINED;
    }
    else if (input[index] != '|') {
        inputRead += 1;
        index += 1;
        S2(input);
    }
    else if (input[index] == '|') {
        inputRead += 1;
        index += 1;
        S3(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S3(const std::string& input) {
    if (index == input.size()) {
        type = TokenType::UNDEFINED;
    }
    else if (input[index] != '#') {
        inputRead += 1;
        index += 1;
        S2(input);
    }
    else if (input[index] == '#') {
        newLines += 1;
    }
    else {
        Serr();
    }
}