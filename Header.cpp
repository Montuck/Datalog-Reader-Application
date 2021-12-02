//
// Created by oblit on 10/23/2021.
//

#include "Header.h"

string Header::getHeader(int index) const {
    return attributes.at(index);
}


void Header::addToAttributes(string toAdd){
    string s = "";
    for (unsigned int i = 0; i < toAdd.size(); i++) {
        if (toAdd.at(i) == ',' ) {
            attributes.push_back(s);
            s = "";
        }
        else {
            s += toAdd.at(i);
        }
    }
    attributes.push_back(s);
}

string Header::getHeaders() {
    string headers = "";
    for (unsigned int i = 0; i < attributes.size(); i++) {
        headers += attributes.at(i);
        if (i != attributes.size() - 1) {
            headers += ",";
        }
    }
    return headers;
}

int Header::getSize() {
    return attributes.size();
}

void Header::addVecAttributes(vector<string> toAdd) {
    attributes = toAdd;
}