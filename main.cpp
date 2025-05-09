#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include "node.h"
#include "problem.h"
#include "heuristics.h"
#include <unordered_set>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// find soltn path 
vector<string> find_solution_path(Node* node) {
    vector<string> actions;
    while (node->parent != nullptr) {
        actions.push_back(node->action);
        node = node->parent;
    }
    reverse(actions.begin(), actions.end());
    return actions;
}

// convert state to string so we can quickly compare
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

vector<string> graph_search(const Problem& problem, int (*heuristic_fn)(const vector<vector<int>>&, const vector<vector<int>>&), ofstream& outFile) {
    struct NodeCompare {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->total_cost() > rhs->total_cost();
        }
    };
    auto global_start_time = high_resolution_clock::now();
    auto last_log_time = global_start_time;

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

    long long int count = 0;
    while (!frontier.empty()) {
        max_queue_size = max(max_queue_size, static_cast<int>(frontier.size()));
        Node* node = frontier.top();
        frontier.pop();

        if (count<6000){
            outFile << "Expanding state with path cost: " << node->path_cost 
                << ", heuristic cost: " << node->heuristic_cost 
                << ", total cost: " << node->total_cost() << endl;
            count++;
       
        
            for (const auto& row : node->state) {
                for (int tile : row) outFile << tile << " ";
                outFile << endl;
            }
            outFile << "------------------" << endl;
        }
         else if(count == 6000){
            outFile<< "States expanded exceeds 6000. For the sake of storage, omitting the remaining states from trace... "<< endl << endl;
            count++;
        }

        if (problem.is_goal(node->state)) {
            outFile << "Nodes expanded: " << nodes_expanded << endl;
            outFile << "Max queue size: " << max_queue_size << endl;
            outFile << "Goal depth: " << node->path_cost << endl;

            vector<string> solution = find_solution_path(node);

            for (Node* n : all_nodes) delete n;
            return solution;
        }

        // if the current state isn't the solution explore
        string state_str = state_to_string(node->state);
        if (explored.find(state_str) == explored.end()) {
            explored.insert(state_str);
            nodes_expanded++;

            // for tracking every 10 mins
            // auto current_time = high_resolution_clock::now();
            // auto time_since_last_log = duration_cast<seconds>(current_time - last_log_time);
            // if (time_since_last_log.count() >= 600) { // 600 seconds = 10 minutes
            //     auto total_elapsed = duration_cast<minutes>(current_time - global_start_time);
            //     outFile << "[Progress Log @ " << total_elapsed.count() << " minutes]" << endl;
            //     outFile << "  Nodes expanded so far: " << nodes_expanded << endl;
            //     outFile << "  Max queue size so far: " << max_queue_size << endl;
            //     outFile << "  Frontier size now: " << frontier.size() << endl;
            //     outFile << "------------------------------" << endl;

            //     last_log_time = current_time; // reset log timer
            // }

            for (const auto& successor : problem.expand_states(node->state)) {
                const auto& action = successor.action;
                const auto& new_state = successor.state;
            
                string successor_str = state_to_string(new_state);
                int new_cost = node->path_cost + 1;
            
                // only push if new state/found a cheaper path
                if (cost_so_far.find(successor_str) == cost_so_far.end() || new_cost < cost_so_far[successor_str]) {
                    cost_so_far[successor_str] = new_cost;
            
                    int heuristic_cost = heuristic_fn(new_state, problem.goal_state);
                    Node* child_node = new Node(new_state, node, action, new_cost, heuristic_cost);
                    frontier.push(child_node);
                    all_nodes.push_back(child_node); 
                }
            }
        }
    }

    for (Node* n : all_nodes) delete n;
    return {};
}


void solve_puzzle(const Problem& problem, int algorithm_choice) {
    ofstream outFile("input1-ucs.txt"); // file to write the output

    switch (algorithm_choice) {
        case 1: {
            cout << "Solving with Uniform Cost Search" << endl;
            auto start = high_resolution_clock::now();
            vector<string> solution = graph_search(problem, uniform_cost, outFile);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            outFile<< "Duration (microseconds): "<< duration.count() << endl;
            for (const auto& action : solution) outFile << action << " ";
            outFile << endl;
            cout<< "Done writing solution to file." << endl;
            break;
        }
        case 2: {
            cout << "Solving with Manhattan Heuristic" << endl;
            auto start = high_resolution_clock::now();
            vector<string> solution = graph_search(problem, manhattan_distance, outFile);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            outFile<< "Duration (microseconds): "<< duration.count() << endl;
            
            
            for (const auto& action : solution) outFile << action << " ";
            outFile << endl;
            cout<< "Done writing solution to file." << endl;
            break;
        }
        default:
            cout << "Invalid algorithm choice." << endl;
    }
    outFile.close(); 
}

int main() {
    cout << "Welcome to the 9 Men in Trench Puzzle.\n";
    // input 1
    vector<vector<int>> initial_state = {
        {0, 2, 3, 4, 5, 6, 7, 8, 9, 1}, // trenches
        {-1, -1, -1, 0, -1, 0, -1, 0, -1, -1} // recesses
    };


    // input 2
    // vector<vector<int>> initial_state = {
    //     {2, 0, 0, 0, 0, 3, 4, 6, 8, 9}, // trenches
    //     {-1, -1, -1, 1, -1, 5, -1, 7, -1, -1} // recesses
    // };

    // input 3
    //  vector<vector<int>> initial_state = {
    //     {1, 2, 3, 4, 5, 6, 0, 0, 8, 9}, // trenches
    //     {-1, -1, -1, 0, -1, 0, -1, 7, -1, -1} // recesses
    // };

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
