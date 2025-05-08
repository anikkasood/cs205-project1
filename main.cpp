#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include "node.h"
#include "problem.h"
#include "heuristics.h"
#include <unordered_set>

using namespace std;

vector<string> find_solution_path(Node* node) {
    vector<string> actions;
    while (node->parent != nullptr) {
        actions.push_back(node->action);
        node = node->parent;
    }
    reverse(actions.begin(), actions.end());
    return actions;
}
string state_to_string(const vector<vector<int>>& state) {
    string result;
    for (const auto& row : state) {
        for (int tile : row) {
            result += to_string(tile) + ",";
        }
    }
    return result;
}

bool is_explored(const vector<vector<int>>& state, const unordered_set<string>& explored) {
    string state_str = state_to_string(state);
    return explored.find(state_str) != explored.end();
}

vector<string> graph_search(const Problem& problem, int (*heuristic_fn)(const vector<vector<int>>&, const vector<vector<int>>&)) {
    struct NodeCompare {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->total_cost() > rhs->total_cost();
        }
    };

    priority_queue<Node*, vector<Node*>, NodeCompare> frontier;
    unordered_set<string> explored;
    vector<Node*> all_nodes; 

    unordered_map<string, int> cost_so_far;

    Node* initial_node = new Node(problem.initial_state, nullptr, "", 0, heuristic_fn(problem.initial_state, problem.goal_state));
    
    string initial_state_str = state_to_string(problem.initial_state);
    cost_so_far[initial_state_str] = 0;

    frontier.push(initial_node);
    all_nodes.push_back(initial_node);

    int nodes_expanded = 0;
    int max_queue_size = 0;

    while (!frontier.empty()) {
       
        max_queue_size = max(max_queue_size, static_cast<int>(frontier.size()));
        Node* node = frontier.top();
        frontier.pop();

        cout << "Expanding state with path cost: " << node->path_cost 
             << ", heuristic cost: " << node->heuristic_cost 
             << ", total cost: " << node->total_cost() << endl;
      
        for (const auto& row : node->state) {
            for (int tile : row) cout << tile << " ";
            cout << endl;
        }
        cout << "------------------" << endl;

        if (problem.is_goal(node->state)) {
            cout << "Nodes expanded: " << nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            cout << "Goal depth: " << node->path_cost << endl;

            vector<string> solution = find_solution_path(node);

            for (Node* n : all_nodes) delete n;
            return solution;
        }

        string state_str = state_to_string(node->state);
        if (explored.find(state_str) == explored.end()) {
            explored.insert(state_str);
            nodes_expanded++;

            for (const auto& successor : problem.expand_states(node->state)) {
                const auto& action = successor.action;
                const auto& new_state = successor.state;
            
                string successor_str = state_to_string(new_state);
                int new_cost = node->path_cost + 1;
            
                // Only push to frontier if the state is new or we found a cheaper path
                if (cost_so_far.find(successor_str) == cost_so_far.end() || new_cost < cost_so_far[successor_str]) {
                    cost_so_far[successor_str] = new_cost;
            
                    int heuristic_cost = heuristic_fn(new_state, problem.goal_state);
                    Node* child_node = new Node(new_state, node, action, new_cost, heuristic_cost);
                    frontier.push(child_node);
                    all_nodes.push_back(child_node); 
                }
            }

            
            // for (const auto& successor : problem.expand_states(node->state)) {
            //     const auto& action = successor.action;
            //     const auto& new_state = successor.state;

            //     string successor_str = state_to_string(new_state);
            //     if (explored.find(successor_str) == explored.end()) {
            //         int path_cost = node->path_cost + 1;
            //         int heuristic_cost = heuristic_fn(new_state, problem.goal_state);

            //         Node* child_node = new Node(new_state, node, action, path_cost, heuristic_cost);
            //         frontier.push(child_node);
            //         all_nodes.push_back(child_node); 
            //     }
            // }
        }
    }

    for (Node* n : all_nodes) delete n;
    return {};
}


void solve_puzzle(const Problem& problem, int algorithm_choice) {
    switch (algorithm_choice) {
        case 1: {
            cout << "Solving with Uniform Cost Search" << endl;
            vector<string> solution = graph_search(problem, uniform_cost);
            for (const auto& action : solution) cout << action << " ";
            cout << endl;
            break;
        }
        case 2: {
            cout << "Solving with Manhattan Heuristic" << endl;
            vector<string> solution = graph_search(problem, manhattan_distance);
            for (const auto& action : solution) cout << action << " ";
            cout << endl;
            break;
        }
        default:
            cout << "Invalid algorithm choice." << endl;
    }
}

int main() {
    cout << "Welcome to the 9 Men in Trench Puzzle.\n";
    
    vector<vector<int>> initial_state = {
        {0, 2, 3, 4, 5, 6, 7, 8, 9, 1}, // trenches
        {-1, -1, -1, 0, -1, 0, -1, 0, -1, -1} // recesses
    };

    vector<vector<int>> goal_state = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, // trenches
        {-1, -1, -1, 0, -1, 0, -1, 0, -1, -1} // recesses
    };

    int algorithm_choice;
    cout << "Choose an algorithm:\n1. Uniform Cost Search\n2. A* with Manhattan Distance\n";
    cin >> algorithm_choice;

    Problem problem(initial_state, goal_state);
    solve_puzzle(problem, algorithm_choice);

    return 0;
}
