//
// Created by oblit on 9/25/2021.
//

#include "Rule.h"

string Rule::getRString() {
    string reString = "";
    reString += headPredicate.getString() + " :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
        reString += bodyPredicates.at(i)->getString() + ",";
    }
    reString.pop_back();
    return reString;
}

void Rule::setHeadPred(Predicate pred) {
    headPredicate = pred;
}

void Rule::setBodPred(vector<Predicate *> bodPred) {
    bodyPredicates = bodPred;
}