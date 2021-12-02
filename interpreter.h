//
// Created by oblit on 10/26/2021.
//

#ifndef TIRED3_INTERPRETER_H
#define TIRED3_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class interpreter {
private:
    DatalogProgram* data;
    Database dBase;

public:
    bool done = true;
    interpreter(DatalogProgram* poggers){
        data = poggers;
    }
    Relation makeRelation(string schemes);
    Tuple makeTuple(string facts);
    Relation evaluatePredicate(Predicate p);
    void addToDatabase();
    void printRelation();
    void evaluate();
    void printQueries(Relation relQuery, unsigned int queryNum);
    void printRules(Relation relRules, int rulesNum);
    Relation ruleEvaluation(Rule rule);
};


#endif //TIRED3_INTERPRETER_H
