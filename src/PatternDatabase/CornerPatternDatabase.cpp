#include<bits/stdc++.h>

#include "CornerPatternDatabase.h"
using namespace std;

// total size = 8! * 3^7 = 40320 * 2187
CornerPatternDatabase::CornerPatternDatabase(uint8_t initialValue)
    : PatternDatabase(40320 * 2187, initialValue) {}

int CornerPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const{
    // Create Permutation Array from corner indexes
    array<uint8_t, 8> perm;
    for(int i=0; i<8; i++){
       perm[i] = cube.getCornerIndex(i);
    }

    // Get Permutation Rank
    int rank = permIndexer.rank(perm);

    // Get Orientation Number
    int orientationNum = 0;
    for(int i=0; i<7; i++){
        orientationNum = orientationNum * 3 + cube.getCornerOrientation(i);
    }

    // combine both to get total permutation index
    return rank * 2187 + orientationNum;
}