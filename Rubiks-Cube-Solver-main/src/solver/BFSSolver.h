#pragma once
#include <bits/stdc++.h>

#include "../cube/RubiksCube.h"
using namespace std;

template<typename T, typename H>
class BFSSolver{

private:
    vector<RubiksCube::MOVE> moves;
    unordered_set<T, H> visited;
    // map that stores the move done on a node (helps in fetching the solution)
    unordered_map<T, RubiksCube::MOVE, H> move_done;

    // does BFS and return the solved rubiks cube
    T bfs(){
        queue<T> q;
        visited.insert(cube);
        q.push(cube);

        while(!q.empty()){
            T node = q.front();
            q.pop();
            if(node.isSolved()) return node;

            for(int i=0; i<18; i++){
                auto currMove = RubiksCube::MOVE(i);
                node.move(currMove);

                if(visited.find(node) == visited.end()){
                    visited.insert(node);
                    q.push(node);
                    move_done[node] = currMove;
                }
                node.invert(currMove);
            }
        }
        return cube;
    }
public:
    T cube;

    BFSSolver(T cube){
        this->cube = cube;
    }

    vector<RubiksCube::MOVE> solve(){
        T solvedCube = bfs();
        assert(solvedCube.isSolved());
        T currCube = solvedCube;

        // trace back to the original from solved cube and get the applied moves
        while(!(currCube == cube)){
            auto move = move_done[currCube];
            moves.push_back(move);
            currCube.invert(move);
        }
        cube = solvedCube;
        reverse(moves.begin(), moves.end());
        return moves;
    }

};