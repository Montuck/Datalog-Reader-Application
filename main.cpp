#include "Lexer.h"
#include "Parser.h"
//#include "DatalogProgram.h"
#include "interpreter.h"
//#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    //Check if command argument is valid
    if (argc != 2) {
        cout << "no file" << endl;
        return 1;
    }
    //Set filename and ifstream
    string fileName = argv[1];
    ifstream fin(fileName);
    string token = "";
    if (fin.is_open()) {
        char c = ' ';
        while (fin.peek() != EOF) {
           c = fin.get();
           token += c;
       }
    }
    else if (!(fin.is_open())) {
        cout << "failure" << endl;
    }
    //build tokenlist
    Lexer* lexer = new Lexer();
    vector<Token*> tokens = lexer->Run(token);
    //remove comments
    vector<Token*>::iterator itr = tokens.begin();
    for (unsigned int i = 0; i < tokens.size(); i++) {
        if((*itr)->getTokenType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin()+i);
            i--;
        }
        else {
            itr++;
        }
    }
    //parse the list of tokens
    Parser* parser = new Parser(tokens);
    parser->parse();
    interpreter purple(parser->toInterpreter());
    purple.addToDatabase();
    //purple.printRelation();
    purple.evaluate();

    //lexer->Print();
    delete lexer;
    delete parser;
    return 0;
}