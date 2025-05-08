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
    return -1; // No valid tile found
}


int find_closest_left(const vector<vector<int>>& state, int start) {
    for (int i = start - 1; i >= 0; --i) {
        if (state[0][i] != 0 && state[0][i] != -1) {
            return i;
        }
    }
    return -1; // No valid tile found
}
// vector<Problem::ExpandedState> Problem::expand_states(const vector<vector<int>>& state) const {
//     vector<ExpandedState> successors;
//     vector<int> blank_trenches = find_blank_trenches(state);
//     vector<int> blank_recesses = find_blank_recesses(state);
//     int n = state[0].size();

//     // Helper function to handle movement from a trench
//     auto move_from_trench = [&](int i, int move, string action_prefix) {
//         vector<vector<int>> new_state = state;
//         new_state[0][i] = state[0][move];
//         new_state[0][move] = 0;
//         string action = action_prefix + to_string(state[0][move]) + " - " + to_string(i + 1) + "\n";
//         successors.push_back({action, new_state});
//     };

//     // Helper function to handle movement from a recess
//     auto move_from_recess = [&](int i, int recess_index, string action_prefix) {
//         vector<vector<int>> new_state = state;
//         int val = state[1][recess_index];
//         new_state[0][i] = val;
//         new_state[1][recess_index] = 0;
//         string action = action_prefix + to_string(val) + " - " + to_string(i + 1) + "\n";
//         successors.push_back({action, new_state});
//     };

//     // TRENCH CASES
//     for (int i : blank_trenches) {
//         vector<vector<int>> new_state;
//         string action;

//         // if it's on the right edge --> find closest left tile
//         if (i == n - 1) {
//             int move = find_closest_left(state, i);
//             if (move < 7 && state[1][7] != 0 && move != -1) {  // pull from closest recess
//                 move_from_recess(i, 7, "recess: ");
//             }

//             if (move != -1) {  // pull from closest trench on left
//                 move_from_trench(i, move, "");
//             }
//         } 
//         // if it's on the left edge
//         else if (i == 0) {
//             int move = find_closest_right(state, i);
//             if (move > 3 && state[1][3] != 0 && move != -1) {  // pull from closest recess
//                 move_from_recess(i, 3, "recess: ");
//             }

//             if (move != -1) {  // pull from closest trench on right
//                 move_from_trench(i, move, "");
//             }
//         } 
//         // if it's in the center
//         else {
//             // Check and pull from recesses 3, 5, and 7 if possible
//             for (int recess : {3, 5, 7}) {
//                 if (state[1][recess] != 0) {
//                     bool path_clear = true;
//                     if (i < recess) {
//                         for (int j = i + 1; j < recess; ++j)
//                             if (state[0][j] != 0) path_clear = false;
//                     } else {
//                         for (int j = recess + 1; j < i; ++j)
//                             if (state[0][j] != 0) path_clear = false;
//                     }

//                     if (path_clear) {
//                         move_from_recess(i, recess, "recess: ");
//                     }
//                 }
//             }

//             // Pull from above
//             if (state[1][i] != 0 && state[1][i] != -1) {
//                 new_state = state;
//                 new_state[0][i] = state[1][i];
//                 new_state[1][i] = 0;
//                 action = to_string(state[1][i]) + " - " + to_string(i + 1) + "\n";
//                 successors.push_back({action, new_state});
//             }

//             // Pull from left
//             int move = find_closest_left(state, i);
//             if (move != -1) {
//                 move_from_trench(i, move, "");
//             }

//             // Pull from right
//             move = find_closest_right(state, i);
//             if (move != -1) {
//                 move_from_trench(i, move, "");
//             }
//         }
//     }

//     // RECESS CASES
//     for (int i : blank_recesses) {
//         // Check if can pull from directly below
//         if (state[0][i] != 0) {
//             vector<vector<int>> new_state = state;
//             new_state[1][i] = state[0][i];
//             new_state[0][i] = 0;
//             string action = "move value: " + to_string(state[0][i]) + " to recess i = " + to_string(i) + "\n";
//             successors.push_back({action, new_state});
//         }

//         // Check if can pull from below and to left
//         int move = find_closest_left(state, i);
//         if (move != -1 && state[0][i] == 0) {
//             vector<vector<int>> new_state = state;
//             new_state[1][i] = state[0][move];
//             new_state[0][move] = 0;
//             string action = "move value: " + to_string(state[0][move]) + " to recess i = " + to_string(i) + "\n";
//             successors.push_back({action, new_state});
//         }

//         // Check if can pull from directly below and to right
//         move = find_closest_right(state, i);
//         if (move != -1 && state[0][i] == 0) {
//             vector<vector<int>> new_state = state;
//             new_state[1][i] = state[0][move];
//             new_state[0][move] = 0;
//             string action = "move value: " + to_string(state[0][move]) + " to recess i = " + to_string(i) + "\n";
//             successors.push_back({action, new_state});
//         }
//     }

//     return successors;
// }

vector<Problem::ExpandedState> Problem::expand_states(const vector<vector<int>>& state) const {
    vector<ExpandedState> successors;
    vector<int> blank_trenches = find_blank_trenches(state);
    vector<int> blank_recesses = find_blank_recesses(state);
    vector<vector<int>> new_state = state;
    int move = 0;
    string action = "";
    int n = state[0].size();

    // TRENCH CASES

    for(int i : blank_trenches){
        // if it's on the right edge --> find closest left tile
        if(i == n-1){
            move = find_closest_left(state, i);
            if (move < 7 && (state[1][7] != 0) && move != -1){ // pull from closest recess
                new_state = state;
                new_state[0][i] = state[1][7]; 
                new_state[1][7] = 0;
                action = "recess: " + to_string(state[1][7]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
            }
            
            // pull from closest trench on left
            if(move != -1){
                new_state = state;
                new_state[0][i] = state[0][move]; 
                new_state[0][move] = 0;
                action = to_string(state[0][move]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
            }
            
        }
        else if(i == 0){ // if it's on the left egde
            move = find_closest_right(state, i);
            if (move > 3 && (state[1][3] != 0) && move != -1){ // pull from closest recess
                new_state = state;
                new_state[0][i] = state[1][3]; 
                new_state[1][3] = 0;
                action = "recess: " +  to_string(state[1][3]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});

            }
            
             // pull from closest trench on right
             if(move != -1){
                new_state = state;
                new_state[0][i] = state[0][move]; 
                new_state[0][move] = 0;
                action = to_string(state[0][move]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
             }
        }
        // if it's in the center
        else{
            // check if can pull from a recess
            if(state[1][3] != 0){
                // check if the path from empty to this recess is clear 
                if( i < 3){ // empty is on the left 
                    bool path_clear = true;
                    for(int j = i + 1; j < 3; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state[0][i] = state[1][3]; 
                        new_state[1][3] = 0;
                        action = "recess: " + to_string(state[1][3]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }
                }
                else{ // empty is on the right
                    bool path_clear = true;
                    for(int j = 3; j < i; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state = state;
                        new_state[0][i] = state[1][3]; 
                        new_state[1][3] = 0;
                        action = "recess: " + to_string(state[1][3]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }

                }

            }

            if(state[1][5] != 0){
                // check if the path from empty to this recess is clear 
                if(i < 5){ // empty is on the left 
                    bool path_clear = true;
                    for(int j = i + 1; j < 5; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state = state;
                        new_state[0][i] = state[1][5]; 
                        new_state[1][5] = 0;
                        action = "recess: " + to_string(state[1][5]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }
                }
                else{ // empty is on the right
                    bool path_clear = true;
                    for(int j = 5; j < i; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state = state;
                        new_state[0][i] = state[1][5]; 
                        new_state[1][5] = 0;
                        action = "recess: " + to_string(state[1][5]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }

                }
                
            }

            if(state[1][7] != 0){
                // check if the path from empty to this recess is clear 
                if(i < 7){ // empty is on the left 
                    bool path_clear = true;
                    for(int j = i + 1; j < 7; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state = state;
                        new_state[0][i] = state[1][7]; 
                        new_state[1][7] = 0;
                        action = "recess: " + to_string(state[1][7]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }
                }
                else{ // empty is on the right
                    bool path_clear = true;
                    for(int j = 7; j < i; j++){
                        if(state[0][j] != 0){
                            path_clear = false;
                            break;
                        }
                    }
                    if(path_clear){
                        new_state = state;
                        new_state[0][i] = state[1][7]; 
                        new_state[1][7] = 0;
                        action = "recess: " + to_string(state[1][7]) + " - " + to_string(i+1) + "\n";
                        successors.push_back({action, new_state});
                    }

                }
            }

            // pull from above 
            if(state[1][i] != 0 && state[1][i] != -1){
                new_state = state;
                new_state[0][i] = state[1][i]; 
                new_state[1][i] = 0;
                action = to_string(state[1][i]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
            }

            // pull from left 
            move = find_closest_left(state, i);
            if(move != -1){
                new_state = state;
                new_state[0][i] = state[0][move]; 
                new_state[0][move] = 0;
                action = to_string(state[0][move]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
            }
            // pull from right
            move = find_closest_right(state, i);
            if(move != -1){
                new_state = state;
                new_state[0][i] = state[0][move];
                new_state[0][move] = 0;
                action = to_string(state[0][move]) + " - " + to_string(i+1) + "\n";
                successors.push_back({action, new_state});
            }


        }
    }

    // RECCESS CASES
    for(int i : blank_recesses){
        // check if can pull from directly below
        if(state[0][i] != 0){
            new_state = state;
            new_state[1][i] = state[0][i]; 
            new_state[0][i] = 0;
            action = to_string(i+1) + " - " + "recess: " + to_string(state[0][i]) + "\n";
            successors.push_back({action, new_state});
        }
        // check if can pull from below and to left
        move = find_closest_left(state, i);
        if (move != -1 && state[0][i] == 0) {
            new_state = state;
            new_state[1][i] = state[0][move]; 
            new_state[0][move] = 0;
            action = to_string(state[0][move]) + " - " + "recess: " + to_string(i+1) + "\n";
            successors.push_back({action, new_state});
        }
        // check if can pull from directly below and to right
        move = find_closest_right(state, i);
        if (move != -1 && state[0][i] == 0) {
            new_state = state;
            new_state[1][i] = state[0][move]; 
            new_state[0][move] = 0;
            action = to_string(state[0][move]) + " - " + "recess: " + to_string(i+1) + "\n";
            successors.push_back({action, new_state});
        }
    }


    return successors;
}

    // resulted in 31
    // /************* Trench to Trench and Recess to Trench *************/
    // for (int empty : blank_trenches) {
    //     // From left trench
    //     for (int i = empty - 1; i >= 0; --i) {
    //         if (state[0][i] != 0) {
    //             bool blocked = false;
    //             for (int j = i + 1; j < empty; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked) {
    //                 new_state = state;  

    //                 new_state[0][empty] = state[0][i];
    //                 new_state[0][i] = 0;
    //                 string action = "(trench): " + to_string(i) + " - " + to_string(empty)+ "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }

    //     // From right trench
    //     for (int i = empty + 1; i < n; ++i) {
    //         if (state[0][i] != 0) {
    //             bool blocked = false;
    //             for (int j = empty + 1; j < i; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked) {
    //                 new_state = state;  
                   
    //                 new_state[0][empty] = state[0][i];
    //                 new_state[0][i] = 0;
    //                 string action = "(trench): " + to_string(i) + " - " + to_string(empty)+ "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }

    //     // From left recess
    //     for (int i = empty - 1; i >= 0; --i) {
    //         if (state[1][i] != 0 && state[1][i] != -1) {
    //             bool blocked = false;
    //             for (int j = i + 1; j < empty; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked && state[0][i] == 0) {
    //                 new_state = state;  
                    
    //                 new_state[0][empty] = state[1][i];
    //                 new_state[1][i] = 0;
    //                 string action = "(trench): " + to_string(i + 10) + " - " + to_string(empty) + "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }

    //     // From right recess
    //     for (int i = empty + 1; i < n; ++i) {
    //         if (state[1][i] != 0 && state[1][i] != -1) {
    //             bool blocked = false;
    //             for (int j = empty + 1; j < i; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked && state[0][i] == 0) {
    //                 new_state = state;  
                  

    //                 new_state[0][empty] = state[1][i];
    //                 new_state[1][i] = 0;
    //                 string action = "(trench): " + to_string(i + 10) + " - " + to_string(empty) + "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }
    // }

    // /************* Trench to Recess *************/
    // for (int empty : blank_recesses) {
    //     // Directly above
    //     if (state[0][empty] != 0) {
    //         new_state = state;
    //         new_state[1][empty] = state[0][empty];
    //         new_state[0][empty] = 0;
    //         string action = "(recess): " + to_string(empty) + " - " + to_string(empty + 10) + "\n";
    //         successors.push_back({action, new_state});
    //     }

    //     // From left trench
    //     for (int i = empty - 1; i >= 0; --i) {
    //         if (state[0][i] != 0) {
    //             bool blocked = false;
    //             for (int j = i + 1; j < empty; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked) {
    //                 new_state = state;
    //                 new_state[1][empty] = state[0][i];
    //                 new_state[0][i] = 0;
    //                 string action = "(recess): " + to_string(i) + " - " + to_string(empty + 10) + "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }

    //     // From right trench
    //     for (int i = empty + 1; i < n; ++i) {
    //         if (state[0][i] != 0) {
    //             bool blocked = false;
    //             for (int j = empty + 1; j < i; ++j)
    //                 if (state[0][j] != 0) blocked = true;
    //             if (!blocked) {
    //                 new_state = state;  
    //                 new_state[1][empty] = state[0][i];
    //                 new_state[0][i] = 0;
    //                 string action = "(recess): " + to_string(i) + " - " + to_string(empty + 10)+ "\n";
    //                 successors.push_back({action, new_state});
    //             }
    //             break;
    //         }
    //     }
    // }


// vector<Problem::ExpandedState> Problem::expand_states(const vector<vector<int>>& state) const {
//     vector<ExpandedState> successors;
//     vector<vector<int>> new_state;
//     vector<int> blank_trenches = find_blank_trenches(state);
//     vector<int> blank_recesses = find_blank_recesses(state);


//     /******* get states for recesses ********/ 
//     for(int empty:blank_trenches){
//         // check if it's a corner spot
//         // else generate pulling from left trench, right trench, or recess to fill
//         // find closest on left
//         if(empty !=0){
//             for(int i = empty; i >= 0; i--) {
//                 if (state[0][i] != 0) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[0][i]; // move tile into empty space
//                     new_state[0][i] = 0; // mark the original spot as empty
//                     string action = "(trench): "+ to_string(i) + " - " + to_string(empty);
//                     successors.push_back({action, new_state});
//                     break;
//                 }
//             }
//         }
//         // find closest on right
//         if(empty != state[0].size() - 1) {
//             for(int i = empty; i < state[0].size(); i++) {
//                 if (state[0][i] != 0) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[0][i]; // move tile into empty space
//                     new_state[0][i] = 0; // mark the original spot as empty
//                     string action = "(trench): "+ to_string(i) + " - " + to_string(empty);
//                     successors.push_back({action, new_state, 1});
//                     break;
//                 }
//             }
//         }
        
//         // if not left corner find closest in recess from left
//         if(empty!=0){
//             for(int i = empty; i >= 0; i--) {
//                 if ((state[0][i] == 0) && (state[1][i] != 0 ) && (state[1][i] != -1)) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[1][i]; // move tile into empty space
//                     new_state[1][i] = 0; // mark the original spot as empty
//                     string action = "(trench): "+ to_string(i+10) + " - " + to_string(empty);
//                     successors.push_back({action, new_state, 1});
//                     break;
//                 }
//             }
//         }
         
//         // if not right corner find closest in recess from right
//          if(empty!= state[0].size() - 1) {
//             for(int i = empty+1; i < state[0].size(); i++) {
//                 if ((state[0][i] == 0) && (state[1][i] != 0 ) && (state[1][i] != -1)) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[1][i]; // move tile into empty space
//                     new_state[1][i] = 0; // mark the original spot as empty
//                     string action = "(trench): "+ to_string(i+10) + " - " + to_string(empty);
//                     successors.push_back({action, new_state});
//                     break;
//                 }
//             }
//         }
//     }

//     /******* get states for recesses ********/ 
//     for(int empty:blank_recesses){
//         // check if can pull from directly below
//         if(state[0][empty]!=0){
//             new_state = state; 
//             new_state[0][empty] = state[1][empty]; // move tile into empty space
//             new_state[1][empty] = 0; // mark the original spot as empty
//             string action = "(recess): "+ to_string(empty+10) + " - " + to_string(empty+10);
//             successors.push_back({action, new_state, 1});
//         }
//         // check if can pull from below and to left
//         for(int i = empty - 1; i >= 0; i--) {
//             if (state[0][i] != 0) {
//                 // found a tile to pull from
//                 new_state = state; 
//                 new_state[1][empty] = state[0][i]; // move tile into empty space
//                 new_state[0][i] = 0; // mark the original spot as empty
//                 string action = "(recess): "+ to_string(i+10) + " - " + to_string(empty+10);
//                 successors.push_back({action, new_state, 1});
//                 break;
//             }
//         }
//         // check if can pull from directly below and to right
//         for(int i = empty + 1; i < state[0].size(); i++) {
//             if (state[0][i] != 0) {
//                 // found a tile to pull from
//                 new_state = state; 
//                 new_state[1][empty] = state[0][i]; // move tile into empty space
//                 new_state[0][i] = 0; // mark the original spot as empty
//                 string action = "(recess): "+ to_string(i+10) + " - " + to_string(empty+10);
//                 successors.push_back({action, new_state, 1});
//                 break;
//             }
//         }
//     }

//     return successors;
// }

//     /******* Generate moves for empty trench spots *******/
//     for (int empty : blank_trenches) {
//         // Pull from left in trench if path is clear
//         for (int i = empty - 1; i >= 0; --i) {
//             if (state[0][i] == 0) continue;

//             bool path_clear = true;
//             for (int k = i + 1; k < empty; ++k) {
//                 if (state[0][k] != 0) {
//                     path_clear = false;
//                     break;
//                 }
//             }

//             if (path_clear) {
//                 new_state = state;
//                 new_state[0][empty] = state[0][i];
//                 new_state[0][i] = 0;
//                 string action = "(trench): "+ to_string(i) + " - " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//             }
//             break; // only closest valid tile
//         }

//         // Pull from right in trench if path is clear
//         for (int i = empty + 1; i < state[0].size(); ++i) {
//             if (state[0][i] == 0) continue;

//             bool path_clear = true;
//             for (int k = i - 1; k > empty; --k) {
//                 if (state[0][k] != 0) {
//                     path_clear = false;
//                     break;
//                 }
//             }

//             if (path_clear) {
//                 new_state = state;
//                 new_state[0][empty] = state[0][i];
//                 new_state[0][i] = 0;
//                 string action = "(trench): "+ to_string(i) + " - " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//             }
//             break; // only closest valid tile
//         }

//         // Pull from left recess if adjacent and valid
//         if (empty > 0 && state[1][empty - 1] != 0 && state[1][empty - 1] != -1) {
//             new_state = state;
//             new_state[0][empty] = state[1][empty - 1];
//             new_state[1][empty - 1] = 0;
//             string action = "(recess): "+ to_string(empty) + " - " + to_string(empty);
//             successors.push_back({action, new_state, 1});
//         }

//         // Pull from right recess if adjacent and valid
//         if (empty < state[1].size() - 1 && state[1][empty + 1] != 0 && state[1][empty + 1] != -1) {
//             new_state = state;
//             new_state[0][empty] = state[1][empty + 1];
//             new_state[1][empty + 1] = 0;
//             string action = "Recess right: pull from " + to_string(empty + 1) + " to trench " + to_string(empty);
//             successors.push_back({action, new_state, 1});
//         }
//     }

//     /******* Generate moves for empty recess spots *******/
//     for (int empty : blank_recesses) {
//         // Pull from trench directly below
//         if (state[0][empty] != 0) {
//             new_state = state;
//             new_state[1][empty] = state[0][empty];
//             new_state[0][empty] = 0;
//             string action = "Pull up from trench " + to_string(empty) + " to recess";
//             successors.push_back({action, new_state, 1});
//         }

//         // Pull from left trench if path is clear
//         for (int i = empty - 1; i >= 0; --i) {
//             if (state[0][i] == 0) continue;

//             bool path_clear = true;
//             for (int k = i + 1; k < empty; ++k) {
//                 if (state[0][k] != 0) {
//                     path_clear = false;
//                     break;
//                 }
//             }

//             if (path_clear) {
//                 new_state = state;
//                 new_state[1][empty] = state[0][i];
//                 new_state[0][i] = 0;
//                 string action = "Pull left from trench " + to_string(i) + " to recess " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//             }
//             break;
//         }

//         // Pull from right trench if path is clear
//         for (int i = empty + 1; i < state[0].size(); ++i) {
//             if (state[0][i] == 0) continue;

//             bool path_clear = true;
//             for (int k = i - 1; k > empty; --k) {
//                 if (state[0][k] != 0) {
//                     path_clear = false;
//                     break;
//                 }
//             }

//             if (path_clear) {
//                 new_state = state;
//                 new_state[1][empty] = state[0][i];
//                 new_state[0][i] = 0;
//                 string action = "Pull right from trench " + to_string(i) + " to recess " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//             }
//             break;
//         }
//     }

//     return successors;
// }

// vector<Problem::ExpandedState> Problem::expand_states(const vector<vector<int>>& state) const {
//     vector<ExpandedState> successors;
//     vector<vector<int>> new_state;
//     vector<int> blank_trenches = find_blank_trenches(state);
//     vector<int> blank_recesses = find_blank_recesses(state);
//     //int row = blank.row, col = blank.col;

   

//     /******* get states for recesses ********/ 
//     for(int empty:blank_trenches){
//         // check if it's a corner spot
//         // else generate pulling from left trench, right trench, or recess to fill
//         // find closest on left
//         if(empty !=0){
//             for(int i = empty; i >= 0; i--) {
//                 if (state[0][i] != 0) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[0][i]; // move tile into empty space
//                     new_state[0][i] = 0; // mark the original spot as empty
//                     string action = "(left) trench: move " + to_string(i) + " to " + to_string(empty);
//                     successors.push_back({action, new_state});
//                     break;
//                 }
//             }
//         }
//         // find closest on right
//         if(empty != state[0].size() - 1) {
//             for(int i = empty; i < state[0].size(); i++) {
//                 if (state[0][i] != 0) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[0][i]; // move tile into empty space
//                     new_state[0][i] = 0; // mark the original spot as empty
//                     string action = "(right) trench: move " + to_string(i) + " to " + to_string(empty);
//                     successors.push_back({action, new_state, 1});
//                     break;
//                 }
//             }
//         }
        
//         // if not left corner find closest in recess from left
//         if(empty!=0){
//             for(int i = empty; i >= 0; i--) {
//                 if ((state[0][i] == 0) && (state[1][i] != 0 ) && (state[1][i] != -1)) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[1][i]; // move tile into empty space
//                     new_state[1][i] = 0; // mark the original spot as empty
//                     string action = "(left) recess: move " + to_string(i) + " to " + to_string(empty);
//                     successors.push_back({action, new_state, 1});
//                     break;
//                 }
//             }
//         }
         
//         // if not right corner find closest in recess from right
//          if(empty!= state[0].size() - 1) {
//             for(int i = empty+1; i < state[0].size(); i++) {
//                 if ((state[0][i] == 0) && (state[1][i] != 0 ) && (state[1][i] != -1)) {
//                     // found a tile to pull from
//                     new_state = state; 
//                     new_state[0][empty] = state[1][i]; // move tile into empty space
//                     new_state[1][i] = 0; // mark the original spot as empty
//                     string action = "(right) recess: move " + to_string(i) + " to " + to_string(empty);
//                     successors.push_back({action, new_state});
//                     break;
//                 }
//             }
//         }
//     }

//     /******* get states for recesses ********/ 
//     for(int empty:blank_recesses){
//         // check if can pull from directly below
//         if(state[0][empty]!=0){
//             new_state = state; 
//             new_state[0][empty] = state[1][empty]; // move tile into empty space
//             new_state[1][empty] = 0; // mark the original spot as empty
//             string action = "(below) from trench: move " + to_string(empty) + " to recess" + to_string(empty);
//             successors.push_back({action, new_state, 1});
//         }
//         // check if can pull from below and to left
//         for(int i = empty - 1; i >= 0; i--) {
//             if (state[0][i] != 0) {
//                 // found a tile to pull from
//                 new_state = state; 
//                 new_state[1][empty] = state[0][i]; // move tile into empty space
//                 new_state[0][i] = 0; // mark the original spot as empty
//                 string action = "(left) from trench: move " + to_string(i) + " to recess " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//                 break;
//             }
//         }
//         // check if can pull from directly below and to right
//         for(int i = empty + 1; i < state[0].size(); i++) {
//             if (state[0][i] != 0) {
//                 // found a tile to pull from
//                 new_state = state; 
//                 new_state[1][empty] = state[0][i]; // move tile into empty space
//                 new_state[0][i] = 0; // mark the original spot as empty
//                 string action = "(right) from trench: move " + to_string(i) + " to recess " + to_string(empty);
//                 successors.push_back({action, new_state, 1});
//                 break;
//             }
//         }
//     }



//     // vector<Move> moves = {
//     //     {"up", -1, 0}, {"down", 1, 0}, {"left", 0, -1}, {"right", 0, 1}
//     // };

//     // for (const auto& move : moves) {
//     //     int new_row = row + move.row_offset;
//     //     int new_col = col + move.col_offset;
//     //     if (new_row >= 0 && new_row < state.size() && new_col >= 0 && new_col < state[0].size()) {
//     //         vector<vector<int>> new_state = state;
//     //         swap(new_state[row][col], new_state[new_row][new_col]);
//     //         successors.push_back({move.action, new_state});
//     //     }
//     // }

//     return successors;
// }
