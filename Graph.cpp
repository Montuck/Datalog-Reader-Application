//
// Created by oblit on 12/2/2021.
//

#include "Graph.h"

////build graphs////
void Graph::buildGraphs(DatalogProgram *data) {
    //iterate through each rule
    for (int i = 0; i < data->rulesSize(); i++) {
        set<int> toAdd;

        //compare each rule body predicate to the head predicate of each rule
        for (unsigned int j = 0; j < data->rules.at(i)->bodyPredicates.size(); j++) {
            for (int k = 0; k < data->rulesSize(); k++) {
                if (data->rules.at(k)->headPredicate.id == data->rules.at(i)->bodyPredicates.at(j)->id) {

                    //add edges to set that match
                    toAdd.insert(k);
                }
            }
        }

        //reverse set and add to reverse graph
        if (antiEdges.empty()) {
            set<int> antiAdd;
            antiEdges.insert(pair<int, set<int>>(i, antiAdd));
        }
        else {
            for (auto s: toAdd) {
                if (antiEdges.find(s) == antiEdges.end()) {
                    set<int> antiAdd;
                    antiAdd.insert(i);
                    antiEdges.insert(pair<int, set<int>>(s, antiAdd));
                } else {
                    antiEdges.find(s)->second.insert(i);
                }
            }
        }

        //add orignal edges to graph
        graphEdges.insert(pair<int, set<int>> (i, toAdd));
    }
}
////depth first search////
void Graph::treeOrder(int n) {
    //check if visited if yes complete function of not move on
    if (visited.find(n)->second == false) {

        //it's been visited
        visited.insert(pair <int, bool> (n, true));

        //if the node is connected
        if (!antiEdges.find(n)->second.empty()) {

            //visit each connected node
            for (auto s : antiEdges.find(n)->second) {
                treeOrder(s);
            }
        }

        //on the way back add to the postorder;
        postorder.push_back(n);
    }
}

////DFS Forest Functions////
void Graph::forestOrder() {
    for (unsigned int i = 0; i < postorder.size(); i++) {
        visited.insert(pair<int, bool> (postorder.at(i), false));
    }
    for (int i = postorder.size()-1; i >= 0; i--) {
        dfsTree(graphEdges.find(postorder.at(i))->second, postorder.at(i));
        SCCs.push_back(toAdd);
        toAdd.clear();
    }
}
void Graph::dfsTree(set<int> edges, int node) { //FIXME need to finish conditions
    visited.find(node)->second = true;
    bool nodesVisited = true;
    for (auto s : edges) {
        if (visited.find(s)->second == false) {
            nodesVisited = false;
        }
    }
    if(!edges.empty() && !nodesVisited) {
        for (auto s : edges) {
            dfsTree(graphEdges.find(postorder.at(s))->second, postorder.at(s));
        }
    }
    toAdd.insert(node);
}

////Integrate it all////
void Graph::printGraph() {
    for (auto m : graphEdges) {
        string toPrint = "";
        toPrint += "R" + to_string(m.first) + ':';
        for (auto s : m.second) {
            toPrint += "R" + to_string(s) + ",";
        }
        if (toPrint.at(toPrint.size()-1) == ',') {
            toPrint.pop_back();
        }
        cout << toPrint << endl;
    }
    cout << endl;
}

bool Graph::isLoop(int s) {
    for (auto m : graphEdges.find(s)->second) {
        if (m == s) {
            return true;
        }
    }
    return false;
}

/*DFS forest reverse graph:
for node in graph
	if not visited
		DFS(node)
end

DFS forest forward graph:
for node in postorder
	if not visited
		DFS node
	     add SCC
end

DFS(node):
mark node as visited
 for each node in adjacency list
	if not visited
		DFS(node)
		add node to postorder stack
add to SCC
end*/