#include<bits/stdc++.h>

#include "PatternDatabase.h"
using namespace std;

PatternDatabase::PatternDatabase(int size, uint8_t initialValue)
    : database(size, initialValue), size(size) {}

uint8_t PatternDatabase::getNumMoves(int index) const{
    return database.get(index);
}

uint8_t PatternDatabase::getNumMoves(const RubiksCube& cube) const{
    int index = getDatabaseIndex(cube);
    return database.get(index);
}

bool PatternDatabase::setNumMoves(int index, uint8_t moves){
    // already set
    if(database.get(index) != 15) return false;

    database.set(index, moves);
    return true;
}

bool PatternDatabase::setNumMoves(const RubiksCube& cube, uint8_t moves){
    int index = getDatabaseIndex(cube);
    return setNumMoves(index, moves);
}

int PatternDatabase::getSize() const{
    return size;    // number of entries in the database
}

void PatternDatabase::toFile(const string &filePath) const{
    ofstream fout(filePath, ios::binary);       // opens the file for writing in binary mode

    if(!fout){
        cout << "Error opening file for writing: " << filePath << endl;
        return;
    }

    // write exactly storage size bytes starting from the memory location returned by getData() into the file
    fout.write((char*)database.getData(), database.getStorageSize());
    fout.close();   // close the file
}

bool PatternDatabase::fromFile(const string &filePath){
    ifstream fin(filePath, ios::binary);    // open file for reading in binary mode

    if(!fin){
        return false;   // Error opening the file for reading
    }
    // read exactly storageSize bytes from the file and store them starting at the memory location returned by getData()
    fin.read((char*)database.getData(), database.getStorageSize());
    fin.close();    // close file

    return true;    // Load successful
}

void PatternDatabase::reset(uint8_t value){
    database.reset(value);
}