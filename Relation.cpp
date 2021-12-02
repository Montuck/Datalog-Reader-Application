//
// Created by oblit on 10/23/2021.
//

#include "Relation.h"

Relation Relation::select1(unsigned int index, string value){
    //initialize Relation obj
    Relation relObj(name, headOfFam.getHeaders());

    //iterate through tuples and select those with the value
    for (Tuple t : tuples) {

        //iterate through values on tuple to find value
        for (unsigned int i = 0; i < t.values.size(); i++) {

            //if value is found create a tuple and add to relation
            if (t.values.at(i) == value && i == index) {
                Tuple tuple(t.getTuples());
                relObj.addTupleToRelation(tuple);
            }
        }
    }

    return relObj;
}

Relation Relation::select2(unsigned int index1, unsigned int index2){
    //initialize Relation obj
    Relation relObj(name, headOfFam.getHeaders());

    //iterate through tuple set
    for (Tuple t : tuples) {

        //if variable at index1 == index2 add to relation's tuple
        if (t.values.at(index1) == t.values.at(index2)) {
            Tuple tuple(t.getTuples());
            relObj.addTupleToRelation(tuple);
        }
    }

    return relObj;
}

Relation Relation::project(vector<int>& indices){
    //initialize Relation obj
    Relation relObj(name, "");


    //iterate through tuple set
    for (Tuple t : tuples) {
        //initialize string to get tuples to add
        vector<string> toAdd;

        //get tuples to add
        for (unsigned int i = 0; i < indices.size(); i++) {
            toAdd.push_back(t.getTuple(indices.at(i)));
        }

        //make tuple and add to relation
        Tuple tuple("");
        tuple = tuple.addTupleVector(toAdd);
        relObj.addTupleToRelation(tuple);
    }

    return relObj;
}

Relation Relation::rename(vector<string>& newName){
    //put in string for relObj
    string headers = "";
    for (unsigned int i = 0; i < newName.size(); i++) {
            headers += newName.at(i);
            if (i != newName.size() - 1) {
                headers += ",";
            }
    }

    //initialize Relation obj
    Relation relObj(name, headers);

    //add tuples to relation
    for (Tuple t : tuples) {
        Tuple tuple(t.getTuples());
        relObj.addTupleToRelation(tuple);
    }

    return relObj;
}

void Relation::addTupleToRelation(Tuple tupperware) {
    tuples.insert(tupperware);
}

void Relation::printYourFace() const {
    for (Tuple t : tuples) {
        bool skipped = false;
        for (unsigned int i = 0; i < t.values.size(); i++) {
            if (headOfFam.getHeader(i) != "") {
                cout << " " << headOfFam.getHeader(i) << "=" << t.values.at(i);
                if (i != t.values.size() - 1) {
                    cout << ",";
                }
                skipped = true;
            }
        }
        if (skipped == true) {
            cout << endl;
        }
    }
}

string Relation::returnName() {
    return name;
}

Header Relation::combineHeaders(Header h1, Header h2) {
    Header addHeaders;
    for (int i = 0; i < h1.getSize(); i++) {
        addHeaders.attributes.push_back(h1.getHeader(i));
    }
    for (int i = 0; i < h2.getSize(); i++) {
        addHeaders.attributes.push_back(h2.getHeader(i));
        for (unsigned int j = 0; j < addHeaders.attributes.size()-1; j++) {
            if (addHeaders.attributes.at(addHeaders.attributes.size()-1) == addHeaders.attributes.at(j)) {
                addHeaders.attributes.pop_back();
            }
        }
    }
    return addHeaders;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, vector<int> indices1, vector<unsigned int> indices2) {
    bool isTrue = true; //check if tuples match

    //set false if tuples don't match at each location
    for (unsigned int i = 0; i < indices1.size(); i++) {
        if(t1.values.at(indices1.at(i)) != t2.values.at(indices2.at(i))) {
            isTrue = false;
            break;
        }
    }

    return isTrue;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, vector<int> indices1, vector<unsigned int> indices2) {
    string forTuple;
    //add values from first tuple
    for (unsigned int i = 0; i < t1.values.size(); i++) {
        forTuple += t1.values.at(i) += ",";
    }
    //add values from second tuple
    for (unsigned int i = 0; i < t2.values.size(); i++) {
        bool adIt = true;
        for (unsigned int j = 0; j < indices2.size(); j++) {
            if (i == indices2.at(j)) {
                adIt = false;
            }
        }
        if (adIt == true) {
            forTuple += t2.values.at(i) += ",";
        }
    }

    //add tuples to tuple
    forTuple.pop_back(); //gets rid of extra comma
    Tuple tupObj(forTuple);
    return tupObj;
}

bool Relation::unionOperation(Relation &r1){
    bool truDat = false;
    Relation relObj(r1.name, this->headOfFam.getHeaders());
    for (auto t1 : r1.tuples) {
        if (tuples.insert(t1).second) {
            truDat = true;
            relObj.addTupleToRelation(t1);
        }
        this->addTupleToRelation(t1);
    }
    r1 = relObj;
    return truDat;
}

Relation Relation::joinOperation(Relation r1) {

    //combine headers
    string newName = r1.returnName();
    Header toAdd;
    toAdd = combineHeaders(headOfFam, r1.headOfFam);
    string addMe = toAdd.getHeaders();
    Relation relObj(newName, addMe);

    //get indices where headers match to check
    vector<int> indices1;
    vector<unsigned int> indices2;
    for (int i = 0; i < this->headOfFam.getSize(); i++) {
        for (int j = 0; j < r1.headOfFam.getSize(); j++) {
            if (this->headOfFam.getHeader(i) == r1.headOfFam.getHeader(j)) {
                indices1.push_back(i);
                indices2.push_back(j);
            }
        }
    }
    //for each tuple in each relation check if tuples can be added then add them
    for (auto t1 : tuples) {
        for (auto t2 : r1.tuples) {

            //check if tuples can combine
            if (isJoinable(t1, t2, indices1, indices2)) {

                //combine
                Tuple tupObj = combineTuples(t1, t2, indices1, indices2);
                relObj.addTupleToRelation(tupObj);
            }
        }
    }

    return relObj;
}