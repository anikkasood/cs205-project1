#include "heuristics.h"

#include <cmath>


int manhattan_distance(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
    int total = 0;

    // for (int i = 0; i < state.size(); ++i) {
    //     for (int j = 0; j < state[i].size(); ++j) {
    //         if (state[i][j] != 0 && state[i][j] != -1) { // Ignore blank tiles
    //             int tile_value = state[i][j];
    //             int goalX = -1, goalY = -1;

    //             // Find the position of the current tile in the goal state
    //             for (int x = 0; x < goal.size(); ++x) {
    //                 for (int y = 0; y < goal[x].size(); ++y) {
    //                     if (goal[x][y] == tile_value) {
    //                         goalX = x;
    //                         goalY = y;
    //                         break;
    //                     }
    //                 }
    //                 if (goalX != -1) break; // Stop searching once the tile is found
    //             }

    //             // Add the Manhattan distance for this tile to the total
    //             total += abs(goalX - i) + abs(goalY - j);
    //         }
    //     }
    //}

    for(int i = 0; i < 13; i++){
        if(state[0][i] !=0){
            total += abs(i - state[0][i] + 1); // distance of the current tile from where it's supposed to be
        }


        if(i==10){
            total += abs(i - state[1][3] + 1);
            total += 1; // move out of the recess
        }
    }

    return total; // Total Manhattan distance
}

//return 0 since uniform cost only looks at cost now and not heuristic
int uniform_cost(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
    return 0;
}


