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





 // results in 29!!
    // int dist = 0;

    // // Find position of sergeant (1)
    // int s_row = -1, s_col = -1;
    // for (int row = 0; row < 2; ++row) {
    //     for (int col = 0; col < state[row].size(); ++col) {
    //         if (state[row][col] == 1) {
    //             s_row = row;
    //             s_col = col;
    //             break;
    //         }
    //     }
    // }

    // dist += std::abs(s_row - 1) + std::abs(s_col - 0);

    // for (int val = 1; val <= 9; ++val) {
    //     for (int row = 0; row < 2; ++row) {
    //         for (int col = 0; col < state[row].size(); ++col) {
    //             if (state[row][col] == val) {
    //                 // Goal is in trench row (row 0), column (val - 1)
    //                 if (row != 0 || col != val - 1) {
    //                     dist += 1;
    //                 }
    //             }
    //         }
    //     }
    // }

    // return dist;
   
   
   
    // int total = 0;

    // for(int i = 0; i < state[1].size(); ++i) {
    //     // recess check
    //     if(state[1][i] != goal[1][i]){
    //         int value = state[1][i]; 
    //         int curr_spot = i; 
    //         total += abs (curr_spot - value - 1); 
    //         total += 1; // +1 b/c need to move out of the recess
    //     }

    //     // trench check
    //     if(state[0][i] != goal[0][i]){
    //         int value = state[0][i]; 
    //         int curr_spot = i; 
    //         total += abs (curr_spot - value - 1); 
    //     }
    // }

    // return total; 