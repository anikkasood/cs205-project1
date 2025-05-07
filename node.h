#ifndef NODE_H

#define NODE_H

#include <vector>
#include <string>

using namespace std;

class Node {
public:
    vector<vector<int>> state;
    Node* parent;

    string action;

    int path_cost;
    int heuristic_cost;

    Node(vector<vector<int>> s, Node* p, string a, int pc, int hc);
    int total_cost() const;
    bool operator<(const Node& other) const;
};

#endif





