//
// Created by oblit on 9/25/2021.
//

#include "DatalogProgram.h"
#include <set>

void DatalogProgram::schemeMaker(vector<Predicate *> pred) {
    schemes = pred;
}

void DatalogProgram::factMaker(vector<Predicate *> pred) {
    facts = pred;
}

void DatalogProgram::queryMaker(vector<Predicate *> pred) {
    queries = pred;
}

void DatalogProgram::ruleMaker(vector<Rule *> rule) {
    rules = rule;
}

string DatalogProgram::getScheme() {
    string schemeString = "";
    for (unsigned int i = 0; i < schemes.size(); i++) {
        schemeString = schemeString + "  " + schemes.at(i)->getString() + "\n";
    }
    return schemeString;
}

string DatalogProgram::getFact() {
    string factString = "";
    for (unsigned int i = 0; i < facts.size(); i++) {
        factString = factString + "  " + facts.at(i)->getString() + ".\n";
    }
    return factString;
}

string DatalogProgram::getQuery() {
    string queryString = "";
    for (unsigned int i = 0; i < queries.size(); i++) {
        queryString = queryString + "  " + queries.at(i)->getString() + "?\n";
    }
    return queryString;
}

string DatalogProgram::getRules() {
    string ruleString = "";
    for (unsigned int i = 0; i < rules.size(); i++) {
        ruleString = ruleString + "  " + rules.at(i)->getRString() + ".\n";
    }
    return ruleString;
}

string DatalogProgram::domain() {
    set<string> domain;
    for (unsigned int i = 0; i < facts.size(); i++) {
        for (unsigned int j = 0; j < facts.at(i)->parameters.size(); j++) {
            domain.insert(facts.at(i)->parameters.at(j)->getParameter());
        }
    }
    string domainString = "Domain(" + to_string(domain.size()) + "):\n";
    set<string>::iterator itr = domain.begin();
    for (unsigned  int i = 0; i < domain.size(); i++) {
        domainString += "  " + *itr + "\n";
        itr++;
    }
    return domainString;
}


int DatalogProgram::schemeSize() {
    return schemes.size();
}

int DatalogProgram::factsSize() {
    return facts.size();
}

int DatalogProgram::querySize() {
    return queries.size();
}

int DatalogProgram::rulesSize() {
    return rules.size();
}