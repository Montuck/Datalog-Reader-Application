//
// Created by oblit on 9/25/2021.
//

#include "Predicate.h"

string Predicate::getString() {
    string reString = id + "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        reString = reString + parameters.at(i)->getParameter() + ",";
    }
    reString.pop_back();
    reString = reString + ")";
    return reString;
}

void Predicate::setID(string val){
    id = val;
}

void Predicate::setParameters(vector<Parameter *> param) {
    parameters = param;
}

