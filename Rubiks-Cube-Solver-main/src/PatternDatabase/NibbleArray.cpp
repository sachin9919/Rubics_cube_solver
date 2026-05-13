#include<bits/stdc++.h>

#include "NibbleArray.h"
using namespace std;

NibbleArray::NibbleArray(int size, uint8_t initialValue){
    this->size = size;
    int bytesNeeded = (size+1)/2;       // e.g. 4 nibbles -> 2 bytes, 5 nibbles -> 3 bytes

    arr.resize(bytesNeeded, 0);
    for(int i=0; i<size; i++){
        set(i, initialValue);
    }
}

uint8_t NibbleArray::get(int pos) const{
    int ind = pos/2;
    /* 
        Example Byte:
         0001  0010
         2i    2i+1
    */
    if(pos % 2 == 0){       // upper 4 bits (4-7)
        return arr[ind] >> 4;
    }
    else{       // lower 4 bits (0-3)
        return arr[ind] & 15;
    }
}

void NibbleArray::set(int pos, int value){
    int ind = pos/2;

    if(pos % 2 == 0){       
        // upper 4 bits (4-7)
        arr[ind] &= 15;   // clear upper 4 bits
        arr[ind] |= (value << 4);
    }
    else{       
        // lower 4 bits (0-3)
        arr[ind] &= 240;    // clear lower 4 bits
        arr[ind] |= value;
    }
}

int NibbleArray::getSize() const{
    return size;
}

int NibbleArray::getStorageSize() const{
    return arr.size();
}

void NibbleArray::reset(uint8_t value){
    for(int i=0; i<size; i++){
        set(i, value);
    }
}

uint8_t* NibbleArray::getData(){
    return arr.data();
}

const uint8_t* NibbleArray::getData() const{
    return arr.data();
}