//
// Created by oblit on 10/23/2021.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include <string>
#include "Relation.h"

using namespace std;

class Database {
private:
    //map<string, Relation> nameToRelation;
    //friend class interpreter;

public:
    map<string, Relation> nameToRelation;
    bool addToDB(string key, Relation relation);
    void printRelatable();
    Relation getRelation(string key);
};


#endif //PROJECT_3_DATABASE_H
