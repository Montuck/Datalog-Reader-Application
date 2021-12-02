//
// Created by oblit on 9/25/2021.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include "string"

using namespace std;


class Parameter {
private:
    string param = "";
    //bool isConstant = false;

public:
    void setParameter(string p);
    string getParameter();
};


#endif //PROJECT_2_PARAMETER_H
