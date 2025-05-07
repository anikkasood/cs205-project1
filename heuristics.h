#ifndef HEURISTICS_H

#define HEURISTICS_H

#include <vector>


using namespace std;

    int manhattan_distance(const vector<vector<int>>& state, const vector<vector<int>>& goal);
    int euclidean_distance(const vector<vector<int>>& state, const vector<vector<int>>& goal);
    int uniform_cost(const vector<vector<int>>& state, const vector<vector<int>>& goal);


#endif


