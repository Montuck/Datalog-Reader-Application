//
// Created by oblit on 10/23/2021.
//

#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <string>

using namespace std;

class Header {
private:
    //vector<string> attributes;
    friend class Relations;

public:
    vector<string> attributes;
    string getHeader(int index) const;
    int getSize();
    void addToAttributes(string toAdd);
    void addVecAttributes(vector<string> toAdd);
    string getHeaders();
};


#endif //PROJECT_3_HEADER_H
