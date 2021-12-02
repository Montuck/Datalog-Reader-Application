//
// Created by oblit on 12/2/2021.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <map>
#include <stack>

using namespace std;

class Graph {
private:
    map<int, set<int>> graphEdges;
    map<int, bool> visited;
    stack<int> postorder;
    set<int> SCCs;

public:
    ////build graphs////
    void buildGraphs();
    ////depth first search////
    void treeOrder();
    void dfsTree();
    ////DFS Forest Functions////
    void forestOrder();
    void SCCFinder();
    ////Integrate it all////

};


#endif
