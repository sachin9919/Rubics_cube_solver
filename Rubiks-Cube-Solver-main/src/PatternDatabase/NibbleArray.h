#pragma once
#include<bits/stdc++.h>
using namespace std;

class NibbleArray{

private:
    vector<uint8_t> arr;    // each position stores two 4-bit values (nibbles)
    int size;   // number of 4-bit values
public:
    // initialize the array of a particular size with a particular value
    NibbleArray(int size, uint8_t initialValue=15);
    
    /*
        Sets the value at the corresponding position in the array to the given position of nibble
        pos -> position of the nibble
        value -> 4-bit value to be stored
    */
    void set(int pos, int value);

    // returns the value stored at the given nibble position
    uint8_t get(int pos) const;

    // returns the number of nibbles stored
    int getSize() const;

    // returns the actual size of the array
    int getStorageSize() const;

    // resets the array with the given value
    void reset(uint8_t value);

    /*
        Returns pointer to the underlying byte array.
        Useful when writing the entire nibble array to a file.
    */
    uint8_t* getData();

    /*
        Returns read-only pointer to the underlying byte array.
        Useful when reading values without modifying the internal storage.
    */
    const uint8_t* getData() const;
};