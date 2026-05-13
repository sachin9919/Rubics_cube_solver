#pragma once
#include<bits/stdc++.h>

#include "../cube/RubiksCube.h"
#include "PatternDatabase.h"
#include "PermutationIndexer.h"
using namespace std;

class CornerPatternDatabase : PatternDatabase{
    
private:
    PermutationIndexer<8> permIndexer;

public:
    CornerPatternDatabase(uint8_t intialValue=15);

    int getDatabaseIndex(const RubiksCube& cube) const override;
};