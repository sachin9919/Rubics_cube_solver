#pragma once
#include <bits/stdc++.h>

#include "../cube/RubiksCube.h"
#include "DFSSolver.h"
using namespace std;

template<typename T, typename H>
class IDDFSSolver{

private:
    int maxDepth;
    vector<RubiksCube::MOVE> moves;

public:
    T cube;

    IDDFSSolver(T cube, int maxDepth){
        this->cube = cube;
        this->maxDepth = maxDepth;
    }

    vector<RubiksCube::MOVE> solve(){
        for(int depth=0; depth <= maxDepth; depth++){
            DFSSolver<T, H> dfsSolver(cube, depth);
            moves = dfsSolver.solve();

            if(dfsSolver.cube.isSolved()){
                cube = dfsSolver.cube;      // make the cube = solvedCube
                break;
            }
        }
        return moves;
    }
};