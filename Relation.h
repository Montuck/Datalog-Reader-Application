//
// Created by oblit on 10/23/2021.
//

#ifndef RELATION_H
#define RELATION_H
#include <set>
#include <iostream>
#include "Tuple.h"
#include "Header.h"

using namespace std;

class Relation {
private:
    //set<Tuple> tuples;
    //string name;
    //Header headOfFam;

public:
    string name;
    set<Tuple> tuples;
    Header headOfFam;
    bool added = false;
    Relation(string nam, string attributes) {
        name = nam;
        headOfFam.addToAttributes(attributes);
        tuples = {};
    }
    //~Relation();
    Relation select1(unsigned int index, string value);
    Relation select2(unsigned int index1, unsigned int index2);
    Relation project(vector<int>& indices);
    Relation rename(vector<string>& newName);
    bool unionOperation(Relation &r1);
    Relation joinOperation(Relation r1);
    Header combineHeaders(Header h1, Header h2);
    bool isJoinable(Tuple t1, Tuple t2, vector<int> indices1, vector<unsigned int> indices2);
    Tuple combineTuples(Tuple t1, Tuple t2, vector<int> indices1, vector<unsigned int> indices2);
    void addTupleToRelation(Tuple tupperware);
    void printYourFace() const;
    string returnName();
};


#endif //PROJECT_3_RELATION_H
