//
// Created by oblit on 10/23/2021.
//

#include "Database.h"

bool Database::addToDB(string key, Relation relation) {
    if (nameToRelation.insert({key, relation}).second) {
        return true;
    }
    else {
        return false;
    }
}

void Database::printRelatable() {
    for (map<string, Relation>::const_iterator itr = nameToRelation.begin(); itr != nameToRelation.end(); itr++) {
        itr->second.printYourFace();
    }
}

Relation Database::getRelation(string key) {
    map<string, Relation>::iterator itr;
    itr = nameToRelation.find(key);
    Relation relObj = itr->second;
    return relObj;
}