#include "problem.h"
#include <algorithm>

Problem::Problem(vector<vector<int>> initial, vector<vector<int>> goal)
    : initial_state(initial), goal_state(goal) {}

bool Problem::is_goal(const vector<vector<int>>& state) const {
    return state == goal_state;
}

vector<int> Problem::find_blank_trenches(const vector<vector<int>>& state) const {
    vector<int> ret = {};
    for (int i = 0; i < state[0].size(); i++) {
        if(state[0][i] == 0){
                ret.push_back(i);
        }
    }
    return ret; // return all empty spots in trenches
}

vector<int> Problem::find_blank_recesses(const vector<vector<int>>& state) const {
    vector<int> ret = {};
    for (int i = 0; i < state[1].size(); i++) {
        if(state[1][i] == 0){
                ret.push_back(i);
        }
    }
    return ret; // return all empty spots in recesses
}

int find_closest_right(const vector<vector<int>>& state, int start) {
    for (int i = start + 1; i < state[0].size(); ++i) {
        if (state[0][i] != 0 && state[0][i] != -1) {
            return i;
        }
    }
    return -1; 
}


int find_closest_left(const vector<vector<int>>& state, int start) {
    for (int i = start - 1; i >= 0; --i) {
        if (state[0][i] != 0 && state[0][i] != -1) {
            return i;
        }
    }
    return -1;
}


vector<Problem::ExpandedState> Problem::expand_states(const vector<vector<int>>& state) const {
    vector<ExpandedState> successors;
    vector<int> blank_trenches = find_blank_trenches(state);
    vector<int> blank_recesses = find_blank_recesses(state);
    vector<vector<int>> new_state;
    string action = "";
    int n = state[0].size();

    // TRENCH CASES (moving into empty trench positions)
    for(int empty_pos : blank_trenches) {
        // from left
        for(int move_pos = empty_pos-1; move_pos >= 0; move_pos--) {
            if(state[0][move_pos] != 0) { 
                bool path_clear = true;
                for(int j = move_pos+1; j < empty_pos; j++) {
                    if(state[0][j] != 0) {
                        path_clear = false;
                        break;
                    }
                }
                if(path_clear) {
                    new_state = state;
                    new_state[0][empty_pos] = state[0][move_pos];
                    new_state[0][move_pos] = 0;
                    action = "move value: " + to_string(state[0][move_pos]) + 
                            " to trench i = " + to_string(empty_pos) + "\n";
                    successors.push_back({action, new_state});
                }
                break; 
            }
        }

        // from right
        for(int move_pos = empty_pos+1; move_pos < n; move_pos++) {
            if(state[0][move_pos] != 0) { 
                bool path_clear = true;
            
                for(int j = empty_pos+1; j < move_pos; j++) {
                    if(state[0][j] != 0) {
                        path_clear = false;
                        break;
                    }
                }
                if(path_clear) {
                    new_state = state;
                    new_state[0][empty_pos] = state[0][move_pos];
                    new_state[0][move_pos] = 0;
                    action = "move value: " + to_string(state[0][move_pos]) + 
                            " to trench i = " + to_string(empty_pos) + "\n";
                    successors.push_back({action, new_state});
                }
                break; 
            }
        }

        // if can pull from recess above (only valid recess positions)
        if((empty_pos == 3 || empty_pos == 5 || empty_pos == 7) && 
           state[1][empty_pos] != 0) {
            new_state = state;
            new_state[0][empty_pos] = state[1][empty_pos];
            new_state[1][empty_pos] = 0;
            action = "move value: " + to_string(state[1][empty_pos]) + 
                    " to trench i = " + to_string(empty_pos) + "\n";
            successors.push_back({action, new_state});
        }
    }

    // RECESS CASES (moving into empty recess positions)
    for(int empty_pos : blank_recesses) {
        if(empty_pos != 3 && empty_pos != 5 && empty_pos != 7) continue;
        
        // pull from trench directly belowy
        if(state[0][empty_pos] != 0) {
            new_state = state;
            new_state[1][empty_pos] = state[0][empty_pos];
            new_state[0][empty_pos] = 0;
            action = "move value: " + to_string(state[0][empty_pos]) + 
                    " to recess i = " + to_string(empty_pos) + "\n";
            successors.push_back({action, new_state});
        }
        // below & left
        else if(state[0][empty_pos] == 0) {
            for(int move_pos = empty_pos-1; move_pos >= 0; move_pos--) {
                if(state[0][move_pos] != 0) {
                    bool path_clear = true;
                    for(int j = move_pos+1; j < empty_pos; j++) {
                        if(state[0][j] != 0) {
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear) {
                        new_state = state;
                        new_state[1][empty_pos] = state[0][move_pos];
                        new_state[0][move_pos] = 0;
                        action = "move value: " + to_string(state[0][move_pos]) + 
                                " to recess i = " + to_string(empty_pos) + "\n";
                        successors.push_back({action, new_state});
                    }
                    break;
                }
            }
            // below & right
            for(int move_pos = empty_pos+1; move_pos < n; move_pos++) {
                if(state[0][move_pos] != 0) {
                    bool path_clear = true;
                    for(int j = empty_pos+1; j < move_pos; j++) {
                        if(state[0][j] != 0) {
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear) {
                        new_state = state;
                        new_state[1][empty_pos] = state[0][move_pos];
                        new_state[0][move_pos] = 0;
                        action = "move value: " + to_string(state[0][move_pos]) + 
                                " to recess i = " + to_string(empty_pos) + "\n";
                        successors.push_back({action, new_state});
                    }
                    break;
                }
            }
        }
    }

    return successors;
}

