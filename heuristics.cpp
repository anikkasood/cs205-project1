#include "heuristics.h"

#include <cmath>


int manhattan_distance(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
    int total = 0;
    // dist of recess
    for(int i = 0; i < state[1].size(); ++i) {
        if(state[1][i] != 0){
            if (state[1][i] != goal[1][i]) {
                int pos_to_be = state[1][i]- 1; // the current value minus 1
                total += abs(pos_to_be - i);
                total += 1; // move out of recess 
            }
        }

        if (state[0][i] != 0){
            if (state[0][i] != goal[0][i]) {
                int pos_to_be = state[0][i]- 1; // the current value minus 1
                total += abs(pos_to_be - i);
            }
        }
    }
    return total;
   
}
//return 0 since uniform cost only looks at cost now and not heuristic
int uniform_cost(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
    return 0;
}
