#pragma once
#include<bits/stdc++.h>

#include "../cube/RubiksCube.h"
#include "NibbleArray.h"
using namespace std;

class PatternDatabase{
private:
    NibbleArray database;   // stores Heuristic
    int size;   // number of entries of the database

public:
    // Initialize a database of given size with given value
    PatternDatabase(int size, uint8_t initialValue=15);

    /*
        Returns the database index(nibble position) corresponding to the given cube state.
        Implementation dependent on the type of database (e.g corner database)
    */
    virtual int getDatabaseIndex(const RubiksCube& cube) const = 0;

    // returns the heuristic value stored at given index
    uint8_t getNumMoves(int index) const;

    // returns the heuristic value stored for the given cube state
    uint8_t getNumMoves(const RubiksCube& cube) const;

    /*
        If index is already set -> return false
        else -> store the given number of moves as heuristic value at the given index and return true
    */
    bool setNumMoves(int index, uint8_t moves);

    // stores the given number of moves as the heuristic value for the given cube state
    bool setNumMoves(const RubiksCube& cube, uint8_t moves);

    // returns the number of entries in the database
    int getSize() const;

    // writes the complete database in the given binary file
    void toFile(const string &filePath) const;

    /*
        Reads and Loads the database values from the binary file
        returns true if file loaded successfully in the database, else false
    */
    bool fromFile(const string &filePath);

    // resets all entries of the database with the given value
    void reset(uint8_t value = 0);
};