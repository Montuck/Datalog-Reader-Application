//
// Created by oblit on 10/23/2021.
//

#ifndef TUPLE_H
#define TUPLE_H
#include <vector>
#include <string>

using namespace std;

class Tuple {
private:
    vector<string> values;
    friend class Relation;

public:
    Tuple(string tupleValues) {
        addTuples(tupleValues);
    }
    //~Tuple();
    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }
    string getTuple(int index);
    void addTuples(string tupperware);
    Tuple addTupleVector(vector<string> v);
    string getTuples();
};


#endif //PROJECT_3_TUPLE_H
