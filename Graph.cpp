//
// Created by oblit on 12/2/2021.
//

#include "Graph.h"

////build graphs////
void Graph::buildGraphs(DatalogProgram data) {
    //iterate through each rule
    for (int i = 0; i < data.rulesSize(); i++) {
        set<int> toAdd;

        //compare each rule head predicate to body predicate of each rule
        for (int j = 0; j < data.rulesSize(); j++) {
            for (int k = 0; k < data.rules.at(j)->bodyPredicates.size(); k++) {
                if (data.rules.at(i)->headPredicate.id == data.rules.at(j)->bodyPredicates.at(k)->id) {

                    //add edges to set that match
                    toAdd.insert(j);
                }
            }
        }

        //reverse set and add to reverse graph
        for (auto s : toAdd) {
            if (antiEdges.find(s) == antiEdges.end()) {
                antiEdges.find(s)->second.insert(i);
            }
            else {
                set<int> antiAdd;
                antiAdd.insert(i);
                antiEdges.insert(pair<int, set<int>>(s, antiAdd));
            }
        }

        //add orignal edges to graph
        graphEdges.insert(pair<int, set<int>> (i, toAdd));
    }
}
////depth first search////
void Graph::treeOrder() {

}
void Graph::dfsTree() {

}
////DFS Forest Functions////
void Graph::forestOrder() {

}
void Graph::SCCFinder() {

}
////Integrate it all////