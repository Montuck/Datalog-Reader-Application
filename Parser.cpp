#include <iostream>
#include "Parser.h"

Parser::~Parser(){
    //TODO Clean up memory
}


DatalogProgram* Parser::toInterpreter() {
    dProgPointer = &dProg;
    return dProgPointer;
}

void Parser::parse() {
    try {
        itr = parseTokens.begin();
        parseDatalog();
    }
    catch (Token errorTolkien){
        cout << "Failure!" << endl << "  " << errorTolkien.toString() << endl;
    }
}

DatalogProgram Parser::parseDatalog(){
    //Check Scheme start
    match((*itr)->getTokenType());
    typeNeeded = TokenType::COLON;
    match((*itr)->getTokenType());
    schemeList();

    //make schemes
    dProg.schemeMaker(pred);
    if (dProg.schemeSize() == 0) {
        Token errorTolkien = **itr;
        throw errorTolkien;
    }
    pred.clear(); //reset predicates

    //Check Facts start
    match((*itr)->getTokenType());
    typeNeeded = TokenType::COLON;
    match((*itr)->getTokenType());
    if ((*itr)->getTokenType() != TokenType::RULES) {
        factList();
    }
    else {
        typeNeeded = TokenType::RULES;
    }

    //make facts
    dProg.factMaker(pred);
    pred.clear(); //reset predicates

    //Check Rules start
    match((*itr)->getTokenType());
    typeNeeded = TokenType::COLON;
    match((*itr)->getTokenType());
    if ((*itr)->getTokenType() != TokenType::QUERIES) {
        ruleList();
    }
    else {
        typeNeeded = TokenType::QUERIES;
    }

    //make rules
    dProg.ruleMaker(rule);
    rule.clear(); //reset rules
    pred.clear(); //reset pred

    //Check Queries start
    match((*itr)->getTokenType());
    typeNeeded = TokenType::COLON;
    match((*itr)->getTokenType());
    queryList();
    typeNeeded = TokenType::EFO;
    match((*itr)->getTokenType());

    //make query
    dProg.queryMaker(pred);
    if (dProg.querySize() == 0) {
        Token errorTolkien = **itr;
        throw errorTolkien;

    }
    pred.clear(); //reset predicates

    /*cout << "Success!" << endl;
    cout << "Schemes(" << dProg.schemeSize() << "):\n" <<  dProg.getScheme();
    cout << "Facts(" << dProg.factsSize() << "):\n" <<  dProg.getFact();
    cout << "Rules(" << dProg.rulesSize() << "):\n" <<  dProg.getRules();
    cout << "Queries(" << dProg.querySize() << "):\n" <<  dProg.getQuery();
    cout << dProg.domain();*/

    return dProg;
}

void Parser::match(TokenType type){
    if (type == typeNeeded) {
        itr++;
    }
    else {
        Token errorTolkien = **itr;
        throw errorTolkien;
    }
}

void Parser::schemeList() {
    Parameter* pa = new Parameter(); //initialize obj to get parameters
    Predicate* pr = new Predicate(); //initialize obj to get predicates
    if((*itr)->getTokenType() != TokenType::FACTS) {
        typeNeeded = TokenType::ID;

        varName = (*itr)->getString(); //set scheme name

        match((*itr)->getTokenType());
        typeNeeded = TokenType::LEFT_PAREN;
        match((*itr)->getTokenType());
        typeNeeded = TokenType::ID;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        idList();
        match((*itr)->getTokenType());

        pr->setID(varName); //set predicates
        pr->setParameters(param);
        pred.push_back(pr);

        param.clear();//reset param

        schemeList();
    }
    else {
        typeNeeded = TokenType::FACTS;
    }
}

void Parser::factList() {
    Parameter* pa = new Parameter(); //initialize obj to get parameters
    Predicate* pr = new Predicate(); //initialize obj to get predicates
    if((*itr)->getTokenType() != TokenType::RULES) {
        typeNeeded = TokenType::ID;

        varName = (*itr)->getString(); //set fact name

        match((*itr)->getTokenType());
        typeNeeded = TokenType::LEFT_PAREN;
        match((*itr)->getTokenType());
        typeNeeded = TokenType::STRING;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        stringList();
        match((*itr)->getTokenType());

        pr->setID(varName); //set predicates
        pr->setParameters(param);
        pred.push_back(pr);

        param.clear();//reset param

        typeNeeded = TokenType::PERIOD;
        match((*itr)->getTokenType());
        factList();
    }
    else {
        typeNeeded = TokenType::RULES;
    }
}

void Parser::ruleList() {
    Rule* ru = new Rule();
    if ((*itr)->getTokenType() != TokenType::QUERIES) {
        headPredicate();
        match((*itr)->getTokenType());
        predicateList();

        ru->setHeadPred(predSingular);
        ru->setBodPred(pred);
        rule.push_back(ru);
        param.clear();//reset param
        pred.clear();//reset pred

        match((*itr)->getTokenType());
        ruleList();
    }
    else {
        typeNeeded = TokenType::QUERIES;
    }
}

void Parser::queryList() {
    Predicate* pr = new Predicate(); //initialize obj to get predicates
    if ((*itr)->getTokenType() != TokenType::EFO) {
        typeNeeded = TokenType::ID;

        varName = (*itr)->getString(); //set fact name

        match((*itr)->getTokenType());
        typeNeeded = TokenType::LEFT_PAREN;
        match((*itr)->getTokenType());
        parameterList();
        typeNeeded = TokenType::RIGHT_PAREN;
        match((*itr)->getTokenType());

        pr->setID(varName); //set predicates
        pr->setParameters(param);
        pred.push_back(pr);

        param.clear();//reset param

        typeNeeded = TokenType::Q_MARK;
        match((*itr)->getTokenType());
        queryList();
    }
    else {
        typeNeeded = TokenType::EFO;
    }
}

void Parser::idList() {
    Parameter* pa = new Parameter(); //initialize parameter
    if((*itr)->getTokenType() != TokenType::RIGHT_PAREN) {
        typeNeeded = TokenType::COMMA;
        match((*itr)->getTokenType());
        typeNeeded = TokenType::ID;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        idList();
    }
    else{
        typeNeeded = TokenType::RIGHT_PAREN;
    }
}

void Parser::stringList() {
    Parameter* pa = new Parameter(); //initialize parameter
    if((*itr)->getTokenType() != TokenType::RIGHT_PAREN) {
        typeNeeded = TokenType::COMMA;
        match((*itr)->getTokenType());
        typeNeeded = TokenType::STRING;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        stringList();
    }
    else {
        typeNeeded = TokenType::RIGHT_PAREN;
    }
}

void Parser::headPredicate() { //CHANGE ME MAYBE
    Parameter* pa = new Parameter(); //initialize obj to get parameters
    if ((*itr)->getTokenType() != TokenType::COLON_DASH) {
        typeNeeded = TokenType::ID;

        varName = (*itr)->getString(); //set pred name

        match((*itr)->getTokenType());
        typeNeeded = TokenType::LEFT_PAREN;
        match((*itr)->getTokenType());
        typeNeeded = TokenType::ID;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        idList();

        predSingular.setID(varName); //set predicates
        predSingular.setParameters(param);

        param.clear();//reset param

        typeNeeded = TokenType::RIGHT_PAREN;
        match((*itr)->getTokenType());
    }
    typeNeeded = TokenType::COLON_DASH;
}

void Parser::predicateList() {
    Predicate* pr = new Predicate(); //initialize obj to get predicates
    if ((*itr)->getTokenType() != TokenType::PERIOD) {
        typeNeeded = TokenType::ID;

        varName = (*itr)->getString(); //set pred name

        match((*itr)->getTokenType());
        typeNeeded = TokenType::LEFT_PAREN;
        match((*itr)->getTokenType());
        parameterList();

        pr->setID(varName); //set predicates
        pr->setParameters(param);
        pred.push_back(pr);
        param.clear();

        typeNeeded = TokenType::RIGHT_PAREN;
        match((*itr)->getTokenType());
        if ((*itr)->getTokenType() == TokenType::PERIOD) {
            typeNeeded = TokenType::PERIOD;
        }
        else {
            typeNeeded = TokenType::COMMA;
            match((*itr)->getTokenType());
            predicateList();
        }
    }
    else {
        typeNeeded = TokenType::PERIOD;
    }
}

void Parser::parameterList() {
    Parameter* pa = new Parameter(); //initialize obj to get parameters
    if ((*itr)->getTokenType() == TokenType::STRING) {
        typeNeeded = TokenType::STRING;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        if ((*itr)->getTokenType() == TokenType::RIGHT_PAREN) {
            typeNeeded = TokenType::RIGHT_PAREN;
        }
        else {
            typeNeeded = TokenType::COMMA;
            match((*itr)->getTokenType());
            parameterList();
        }
    }
    else if ((*itr)->getTokenType() == TokenType::ID) {
        typeNeeded = TokenType::ID;

        pa->setParameter((*itr)->getString()); //set parameters
        param.push_back(pa);

        match((*itr)->getTokenType());
        if ((*itr)->getTokenType() == TokenType::RIGHT_PAREN) {
            typeNeeded = TokenType::RIGHT_PAREN;
        }
        else {
            typeNeeded = TokenType::COMMA;
            match((*itr)->getTokenType());
            parameterList();
        }
    }
    else {
        Token errorTolkien = **itr;
        throw errorTolkien;
    }
}