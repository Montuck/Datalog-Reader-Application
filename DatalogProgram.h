//
// Created by oblit on 9/25/2021.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <vector>
#include "Predicate.h"
#include "Rule.h"
using namespace std;

class DatalogProgram {
private:
    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Predicate*> queries;
    vector<Rule*> rules;
    friend class interpreter;
    friend class Graph;

public:

    void schemeMaker(vector<Predicate*> pred);
    void factMaker(vector<Predicate*> pred);
    void queryMaker(vector<Predicate*> pred);
    void ruleMaker(vector<Rule*> rule);
    string getScheme();
    string getFact();
    string getQuery();
    string getRules();
    string domain();
    int schemeSize();
    int factsSize();
    int querySize();
    int rulesSize();
};


#endif //PROJECT_2_DATALOGPROGRAM_H
