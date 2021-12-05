//
// Created by oblit on 9/25/2021.
//

#ifndef RULE_H
#define RULE_H
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate*> bodyPredicates;
    friend class interpreter;
    //friend class DatalogProgram;
    friend class Graph;

public:
    //vector<Predicate*> bodyPredicates;
    string getRString();
    void setHeadPred(Predicate pred);
    void setBodPred(vector<Predicate*> bodPred);
};


#endif //PROJECT_2_RULE_H
