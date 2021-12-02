//
// Created by oblit on 10/23/2021.
//

#include "Tuple.h"

string Tuple::getTuple(int index) {
    string tempString = values.at(index);
    return values.at(index);
}

void Tuple::addTuples(string tupperware) {
    string s = "";
    for (unsigned int i = 0; i < tupperware.size(); i++) {
        s += tupperware.at(i);
        if (tupperware.at(i) == ',') {
            s.pop_back();
            values.push_back(s);
            s = "";
        }
    }
    values.push_back(s);
}

string Tuple::getTuples() {
    string getTuple = "";
    for (unsigned int i = 0; i < values.size(); i++) {
        getTuple += values.at(i);
        if (i != values.size()-1) {
            getTuple += ",";
        }
    }
    return getTuple;
}

Tuple Tuple::addTupleVector(vector<string> v) {
    string toAdd = "";
    for (unsigned int i = 0; i < v.size(); i++) {
        toAdd += v.at(i);
        if (i != v.size()-1) {
            toAdd += ",";
        }
    }
    Tuple tuple(toAdd);
    return tuple;
}