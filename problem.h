#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <string>

using namespace std;

class Problem {
public:
    vector<vector<int>> initial_state;
    vector<vector<int>> goal_state;

    Problem(vector<vector<int>> initial, vector<vector<int>> goal);

    bool is_goal(const vector<vector<int>>& state) const;
    

    vector<int> find_blank_trenches(const vector<vector<int>>& state) const;
    vector<int> find_blank_recesses(const vector<vector<int>>& state) const;
  

    struct ExpandedState {
        string action;
        vector<vector<int>> state;
        int cost;
    };

    vector<ExpandedState> expand_states(const vector<vector<int>>& state) const;
};

#endif



