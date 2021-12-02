#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "Add.h"
#include "Comma.h"
#include "Left_Paren.h"
#include "Multiply.h"
#include "Period.h"
#include "Q_Mark.h"
#include "Queries.h"
#include "Right_Paren.h"
#include "Rules.h"
#include "Schemes.h"
#include "String.h"
#include "ID.h"
#include "Comment.h"
#include "Facts.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new RulesAutomaton());//works
    automata.push_back(new QueriesAutomaton());//works
    automata.push_back(new SchemesAutomaton());//works
    automata.push_back(new FactsAutomaton());//works
    automata.push_back(new ColonAutomaton());//works
    automata.push_back(new IDAutomaton());//works
    automata.push_back(new Left_Paren_Automaton());//works
    automata.push_back(new StringAutomaton());//works
    automata.push_back(new CommaAutomaton());//works
    automata.push_back(new AddAutomaton());//works
    automata.push_back(new MultiplyAutomaton());//works
    automata.push_back(new Right_Paren_Automaton());//works
    automata.push_back(new ColonDashAutomaton());//works
    automata.push_back(new Q_Mark_Automaton());//works
    automata.push_back(new PeriodAutomaton());//works
    automata.push_back(new CommentAutomaton());//works
    // TODO: Add the other needed automata here
}

vector<Token*> Lexer::Run(std::string& input) {
    int lineNumber = 1;
    int maxRead;
    Automaton *maxAutomaton;
    int inputRead;
    Token *newToken = NULL;
    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.front();
        while (isspace(input[0])) {
            if (input[0] == '\n') {
                lineNumber += 1;
            }
            input.erase(0, 1);
        }
        if (input.size() == 0){
            break;
        }
        for (unsigned int i = 0; i < automata.size(); i++) {
            inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        if (maxRead > 0) {
            string newInput = input.substr(0,maxRead);
            newToken = maxAutomaton->CreateToken(newInput, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else{
            maxRead = 1;
            newToken = new Token(TokenType::UNDEFINED, input.substr(0 ,maxRead), lineNumber);
            tokens.push_back(newToken);
        }
        input.erase(0, maxRead);
    }
    tokens.push_back(new Token(TokenType::EFO, "", lineNumber));
    return tokens;
}

void Lexer::Print() {
    for (unsigned int i = 0; i < tokens.size(); i++) {
        cout << tokens.at(i)->toString() << endl;
    }
    cout << "Total Tokens = " << tokens.size() << endl;
}

