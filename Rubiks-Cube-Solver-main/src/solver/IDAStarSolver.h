#pragma once
#include <bits/stdc++.h>
#include "../cube/RubiksCube.h"
#include "../PatternDatabase/PatternDatabase.h"

using namespace std;

template<typename T, typename H>
class IDAStarSolver{
private:
    vector<RubiksCube::MOVE> moves;
    PatternDatabase<T> patternDB;   // used to get h value for a cube state
    unordered_map<T, RubiksCube::MOVE, H> move_done;    // move done to reach a cube state

    struct Node{
        T cube;
        int g;      // dist from start state
        int h;       // estimated distance from goal state
        Node(T _cube, int _g, int _h) : cube(_cube), g(_g), h(_h) {}
    };

    // sort the pq based on smaller f value
    struct Compare{
        bool operator()(Node const &n1, Node const &n2) const{
            if(n1.g + n1.h == n2.g + n2.h) return n1.h > n2.h;
            return n1.g + n1.h > n2.g + n2.h;
        }
    };

    // if solved then return true
    // else return (false, next bound)
    pair<bool, int> AStar(int threshold){
        priority_queue<Node, vector<Node>, Compare> pq;
        unordered_map<T, int, H> dist;      // stores the best g to reach a particular cube state

        auto start = Node(cube, 0, patternDB.getEstimate(cube));
        dist[start.cube] = 0;
        pq.push(start);
        
        int nextBound = 1e9;    // will store the minimum of f values of the pruned nodes(nodes having f > threshold)
        while(!pq.empty()){
            Node node = pq.top();
            pq.pop();
            if(node.g > dist[node.cube]) continue;

            int f = node.g + node.h;

            if(f > threshold){      // prune
                nextBound = min(nextBound, f);
                continue;
            }
            if(node.cube.isSolved()){
                T solvedCube = node.cube;
                T curr = solvedCube;
                moves.clear();

                while(!(curr == start.cube)){
                    RubiksCube::MOVE mv = move_done[curr];
                    moves.push_back(mv);
                    curr.invert(mv);
                }

                reverse(moves.begin(), moves.end());
                cube = solvedCube;      // update the member cube with the solved cube
                return {true, threshold};
            }

            for(int i=0; i<18; i++){
                RubiksCube::MOVE mv = RubiksCube::MOVE(i);
                node.cube.move(mv);

                int new_g = node.g + 1;
                int new_h = patternDB.getEstimate(node.cube);

                // if found better g(depth) to reach that state (indirectly better f = g + h(remains same for a state))
                if(dist.find(node.cube) == dist.end() || new_g < dist[node.cube]){
                    dist[node.cube] = new_g;
                    move_done[node.cube] = mv;
                    pq.push({node.cube, new_g, new_h});
                }

                node.cube.invert(mv);
            }
        }
        return {false, nextBound};
    }
public:
    T cube;
    IDAStarSolver(T cube){
        this->cube = cube;
    }

    vector<RubiksCube::MOVE> solve(){
        int threshold = patternDB.getEstimate(cube);
        while(true){
            move_done.clear();
            auto it = AStar(threshold);
            if(it.first) break;     // if cube solved then exit the loop and return ans

            if(it.second == 1e9) break;
            threshold = it.second;  // increase the threshold to the next bound
        }
        return moves;
    }
};