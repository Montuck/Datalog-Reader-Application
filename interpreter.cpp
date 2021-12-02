//
// Created by oblit on 10/26/2021.
//

#include "interpreter.h"

Relation interpreter::makeRelation(string schemes){
    int pos = schemes.find('(');
    string name = schemes.substr(0, pos);
    name.erase(0, 2);
    schemes = schemes.substr(pos);
    pos = schemes.find(')');
    string attributes = schemes.substr(1, pos);
    attributes.pop_back();
    Relation relation(name, attributes);
    return relation;
}

Tuple interpreter::makeTuple(string facts) {
    int pos = facts.find('(');
    facts = facts.substr(pos);
    pos = facts.find(')');
    string tuples = facts.substr(1, pos-1);
    Tuple tuple(tuples);
    return tuple;
}

void interpreter::addToDatabase(){
    //get schemes
    string schemes = data->getScheme();

    //for the number of schemes
    for (int i = 0; i < data->schemeSize(); i++) {

        //get facts
        string facts = data->getFact();
        Relation relation = makeRelation(schemes);
        int pos = schemes.find('\n'); //keep track of when the newline is
        schemes = schemes.substr(pos+1); //reduce schemes string

        //for number of facts
        for (int i = 0; i < data->factsSize(); i++) {
            string key = relation.returnName();
            string match = facts;
            pos = match.find('(');
            match = match.substr(0, pos);
            match.erase(0,2);
            if (key == match) {
                Tuple tuple = makeTuple(facts);
                relation.addTupleToRelation(tuple);
                pos = facts.find('\n');
                facts.erase(0, pos+1);
            }
            else {
                pos = facts.find('\n');
                facts.erase(0, pos+1);
            }
        }
        dBase.addToDB(relation.returnName(), relation);
    }
}

Relation interpreter::evaluatePredicate(Predicate p) {
    //variables for functions
    map<string, int> tracker;
    vector<int> indices;
    vector<string> names;

    //initialize relation
    Relation relObj = dBase.getRelation(p.id);

    //check each parameter
    for (unsigned int i = 0; i < p.parameters.size(); i++) {

        //if constant
        if (p.parameters.at(i)->getParameter().at(0) == '\'') {
            relObj = relObj.select1(i, p.parameters.at(i)->getParameter());
        }

        //if variable
        else {
            //if 2 instances select2
            if (tracker.find(p.parameters.at(i)->getParameter()) != tracker.end()) {
                relObj = relObj.select2(tracker.find(p.parameters.at(i)->getParameter())->second, i);
            }
            //if 1 instance mark for project and rename
            else {
                tracker.insert({p.parameters.at(i)->getParameter(), i});
                names.push_back(p.parameters.at(i)->getParameter());
                indices.push_back(i);
            }
        }
    }
    //perform project and rename0
    relObj = relObj.project(indices);
    relObj = relObj.rename(names);

    return relObj;
}

void interpreter::evaluate() {
    int schemeCounter = 0;
    //evaluate rules
    cout << "Rule Evaluation" << endl;
    while (done) {
        done = false;
        Relation relObj("", "");
        //cout << data->rules.at(schemeCounter)->getRString() << "." << endl;
        for (int i = 0; i < data->rulesSize(); i++) {
            printRules(ruleEvaluation(*data->rules.at(i)), i);
        }
        schemeCounter++;
    }

    //print how many schemes were populated
    cout << endl << "Schemes populated after " << schemeCounter << " passes through the Rules." << endl << endl;

    //evaluate queries
    cout << "Query Evaluation" << endl;
    for (int i = 0; i < data->querySize(); i++) {
        printQueries(evaluatePredicate(*data->queries.at(i)), i);
    }
}

void interpreter::printQueries(Relation relQuery, unsigned int queryNum) {
    //output ID
    cout << data->queries.at(queryNum)->id << "(";

    //output parameters
    for (unsigned  int i = 0; i < data->queries.at(queryNum)->parameters.size(); i++) {
        cout << data->queries.at(queryNum)->parameters.at(i)->getParameter();
        if (i != data->queries.at(queryNum)->parameters.size()-1) {
            cout << ",";
        }
    }
    cout << ")?";

    //yes or no
    if (relQuery.tuples.empty()) {
        cout << " No" << endl;
    }
    else {
        cout << " Yes(" << relQuery.tuples.size() << ")" << endl;
    }

    //output relation
    relQuery.printYourFace();
}

Relation interpreter::ruleEvaluation(Rule rule) {
    vector<Relation> relations; //vector of intermediate relations
    //evaluate body predicates and add to vector of relations
    for (unsigned int i = 0; i < rule.bodyPredicates.size(); i++) {
        Relation relObj = evaluatePredicate(*rule.bodyPredicates.at(i));
        relations.push_back(relObj);
    }

    Relation finalRelation = relations.at(0); //relation to combine everything with
    //if more than 1 relation on rhs join them all
    if (relations.size() >= 2) {
        for (unsigned int i = 1; i < relations.size(); i++) {
            finalRelation = finalRelation.joinOperation(relations.at(i));
        }
    }

    vector<int> indices; //keeps track of column location
    vector<string> newName; //gets headers to add to final relation
    //get the indices of the columns to project and get the headers to add
    for (unsigned int i = 0; i < rule.headPredicate.parameters.size(); i++) {
        for (int j = 0; j < finalRelation.headOfFam.getSize(); j++) {
            if (rule.headPredicate.parameters.at(i)->getParameter() == finalRelation.headOfFam.getHeader(j)) {
                indices.push_back(j);
                newName.push_back(rule.headPredicate.parameters.at(i)->getParameter());
            }
        }
    }
    finalRelation = finalRelation.project(indices); //project
    finalRelation = finalRelation.rename(newName); //rename
    finalRelation.name = rule.headPredicate.id;

    //union finalRelation with matching relation from database
    //FIXME I am not changing the tuples in finalRelation to print to reflect what was added in the Database
    bool tempdone = dBase.nameToRelation.at(finalRelation.name).unionOperation(finalRelation);

    if (done) {
        //nothing
    }
    else {
        done = tempdone;
    }
    return finalRelation;
}

void interpreter::printRules(Relation relRules, int rulesNum) {
    //output rule
        cout << data->rules.at(rulesNum)->headPredicate.getString() << " :- ";
        for (unsigned int i = 0; i < data->rules.at(rulesNum)->bodyPredicates.size(); i++) {
            cout << data->rules.at(rulesNum)->bodyPredicates.at(i)->getString();
            if (i != data->rules.at(rulesNum)->bodyPredicates.size() - 1) {
                cout << ",";
            } else {
                cout << ".";
            }
        }
        cout << endl;

        //output relation
    if (done) {
        relRules.printYourFace();
    }
}
