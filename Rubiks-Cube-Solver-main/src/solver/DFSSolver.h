#pragma once
#include <bits/stdc++.h>

#include "../cube/RubiksCube.h"
using namespace std;

template<typename T, typename H>
class DFSSolver{

private:
    int maxDepth;
    vector<RubiksCube::MOVE> moves;
    // unordered_map<T, bool, H> visited;

    bool dfs(int depth){
        if(cube.isSolved()) return true;
        if(depth >= maxDepth) return false;
        // visited[cube] = true;
        for(int i=0; i<18; i++){
            moves.push_back(RubiksCube::MOVE(i));
            cube.move(RubiksCube::MOVE(i));
            
            // if(!visited[cube])
                if(dfs(depth+1)) return true;

            moves.pop_back();
            cube.invert(RubiksCube::MOVE(i));
        }
        return false;
    }
public:
    T cube;
    
    DFSSolver(T cube, int maxDepth = 8){
        this->cube = cube;
        this->maxDepth = maxDepth;
    }

    vector<RubiksCube::MOVE> solve(){
        // if(dfs(0)) return moves;
        // cout << "FAILED TO SOLVE" << endl;
        // return {};
        dfs(0);
        return moves;
    }
};