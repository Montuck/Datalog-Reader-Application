#include "Token.h"
#include <iostream>

Token::Token(TokenType token, std::string description, int line) {
    type = token;
    lineNumber = line;
    value = description;
}

string Token::toString() {
    string output = "";
    switch(type) {
        case TokenType::COLON:
            output = "(COLON,\":\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::COLON_DASH:
            output = "(COLON_DASH,\":-\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::COMMA:
            output = "(COMMA,\",\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::PERIOD:
            output = "(PERIOD,\".\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::Q_MARK:
            output = "(Q_MARK,\"?\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::LEFT_PAREN:
            output = "(LEFT_PAREN,\"(\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::RIGHT_PAREN:
            output = "(RIGHT_PAREN,\")\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::MULTIPLY:
            output = "(MULTIPLY,\"*\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::ADD:
            output =  "(ADD,\"+\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::SCHEMES:
            output = "(SCHEMES,\"Schemes\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::FACTS:
            output = "(FACTS,\"Facts\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::RULES:
            output = "(RULES,\"Rules\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::QUERIES:
            output = "(QUERIES,\"Queries\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::ID:
            output = "(ID,\"" + value + "\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::STRING:
            output = "(STRING,\"" + value + "\"," + to_string(lineNumber) + ")";
            break;
            /*
        case TokenType::COMMENT:
            output = "(COMMENT,\"" + value + "\"," + to_string(lineNumber) + ")";
            break;
             */
        case TokenType::EFO:
            output = "(EOF,\"\"," + to_string(lineNumber) + ")";
            break;
        case TokenType::UNDEFINED:
            output = "(UNDEFINED,\"" + value + "\"," + to_string(lineNumber) + ")";
            break;
        default: return "nothing"; break;
    }
    return output;
}

void Token::changeType() {
    type = TokenType::UNDEFINED;
}

TokenType Token::getTokenType() {
    return type;
}

string Token::getString() {
    return value;
}
