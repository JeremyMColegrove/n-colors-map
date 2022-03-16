#include <iostream>
#include "Node.h"
#include <vector>
#include "Node.h"

#define NUM_COLORS 3
class Node {
public:
    std::vector<Node*> children;
    int color = -1;
    std::string name;
    void connect(Node &node) {
        children.push_back(&node);
        node.children.push_back(this);
    }
};

int backtrack(std::vector<Node*> *graph);
int is_valid (std::vector<Node*> *graph);
int main() {


    // create all of our nodes
    Node WA, NT, Q, NSW, SA, V, T;
    WA.name = "WA";
    NT.name = "NT";
    Q.name = "Q";
    NSW.name = "NSW";
    SA.name = "SA";
    V.name = "V";
    T.name = "T";


    // connect up all of our nodes
    SA.connect(WA);
    SA.connect(NT);
    SA.connect(Q);
    SA.connect(NSW);
    SA.connect(V);
    WA.connect(NT);
    NT.connect(Q);
    Q.connect(NSW);
    NSW.connect(V);


    // add all of the nodes to our graph
    std::vector<Node*> graph;
    graph.push_back(&WA);
    graph.push_back(&NT);
    graph.push_back(&Q);
    graph.push_back(&NSW);
    graph.push_back(&SA);
    graph.push_back(&V);
    graph.push_back(&T);

    int result = backtrack(&graph);
    if (!result) {
        printf("No solution found!\n");
        exit(0);
    }

    // print out each states colors
    char *colors[NUM_COLORS] = {"Red", "Green","Blue"};//, "Orange"};
    for (int i=0; i<graph.size(); i++) {
        printf("%s=%s\n", graph[i]->name.c_str(), colors[graph[i]->color]);
    }

    return 0;
}

/*
 * recursively tries coloring each state and checking if it is valid
 */
int backtrack(std::vector<Node*> *graph) {
    // flag for unvisited nodes
    int finished = 1;
    // go through all nodes
    for (int i=0; i< graph->size(); i++) {
        // get the current node
        Node *node = graph->at(i);
        // check if unvisited
        if (node->color > -1) continue;
        // set unvisited flag
        finished = 0;
        // try each color
        for (int color=0; color<NUM_COLORS; color++) {
            // set node to color
            node->color = color;
            // check if valid and move to next node
            if (is_valid(graph) && backtrack(graph)) return 1;
        }
    }

    // check if all nodes visited and map is valid
    return (finished && is_valid(graph));
}


/*
 * Takes a pointer to the graph and returns 1 if the current colors on map are valid, 0 if it is not
 */
int is_valid(std::vector<Node*> *graph) {
    // go through each node
    for (int index=0; index < graph->size(); index++) {
        // get current node
        Node *node = graph->at(index);
        // go through all of its children
        for (int i_child=0; i_child<node->children.size(); i_child++) {
            // get child node
            Node *child = node->children.at(i_child);
            // check if colors are assigned and not equal
            if (child->color == node->color && node->color > -1) {
                // two colors are assigned and the same, so not valid
                return 0;
            }
        }
    }
    return 1;
}
