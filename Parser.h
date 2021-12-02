#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include <vector>
#include <string>

using namespace std;

class Parser {
private:
    vector<Token*>::iterator itr;
    vector<Token*> parseTokens;
    TokenType typeNeeded;
    string varName;
    vector<Parameter*> param;
    vector<Predicate*> pred;
    Predicate predSingular;
    vector<Rule*> rule;
    DatalogProgram dProg;
    DatalogProgram *dProgPointer;

public:
    Parser(vector<Token*> tokens) {
        typeNeeded = TokenType::SCHEMES;
        parseTokens = tokens;
    }
    ~Parser();
    void parse();
    DatalogProgram parseDatalog();
    void match(TokenType type);
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void idList();
    void stringList();
    void headPredicate();
    void predicateList();
    void parameterList();
    DatalogProgram* toInterpreter();
};


#endif //PROJECT_2_PARSER_H
