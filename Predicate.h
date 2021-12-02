//
// Created by oblit on 9/25/2021.
//

#ifndef PREDICATE_H
#define PREDICATE_H
#include "Parameter.h"
#include <string>
#include <vector>
#include <set>

using namespace  std;

class Predicate {
private:
    //string id = "";
    //vector<Parameter*> parameters;
    friend class DatalogProgram;

public:
    string id = "";
    vector<Parameter*> parameters;
    string getString();
    void setID(string val);
    void setParameters(vector<Parameter*> param);
};


#endif //PROJECT_2_PREDICATE_H
