//
// Created by oblit on 12/2/2021.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <map>
#include <stack>
#include <iostream>
#include <vector>
#include "DatalogProgram.h"

using namespace std;

class Graph {
private:
    map<int, set<int>> graphEdges;
    map<int, set<int>> antiEdges;
    map<int, bool> visited;
    //stack<int> postorder;
    vector<set<int>> SCCs; //might not want to have in the class, think about moving it outside in the interpreter
    vector<int> postorder;
    set<int> toAdd;
    friend class interpreter;

public:
    ////build graphs////
    void buildGraphs(DatalogProgram *data);
    ////depth first search////
    void treeOrder(int n);
    ////DFS Forest Functions////
    void forestOrder();
    void dfsTree(set<int> edges, int node);
    void SCCFinder();
    ////Integrate it all////
    void printGraph();
    bool isLoop(int s);

};


#endif
