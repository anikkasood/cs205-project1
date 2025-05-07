#include "node.h"

#include <cmath>

Node::Node(vector<vector<int>> s, Node* p, string a, int pc, int hc)
    : state(s), parent(p), action(a), path_cost(pc), heuristic_cost(hc) {}

int Node::total_cost() const {
    return path_cost + heuristic_cost;
}
bool Node::operator<(const Node& other) const {
    return total_cost() > other.total_cost();
}




