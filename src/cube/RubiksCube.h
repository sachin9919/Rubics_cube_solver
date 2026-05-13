#pragma once
#include<bits/stdc++.h>
using namespace std;

class RubiksCube{

public:
    enum class FACE{
        UP, LEFT, FRONT, RIGHT, BACK, DOWN
    };

    enum class MOVE{
        U, U_PRIME, U2,
        L, L_PRIME, L2,
        F, F_PRIME, F2,
        R, R_PRIME, R2,
        B, B_PRIME, B2,
        D, D_PRIME, D2
    };

    enum class COLOR{
        WHITE, GREEN, RED, BLUE, ORANGE, YELLOW, UNKNOWN
    };
    

    // returns if the rubiks cube is solved or not
    virtual bool isSolved() const = 0;


    // print function (planar representation)
    void print() const;

    /*
     * Print the Rubiks Cube in Planar format.
     *
     * The RubiksCube is opened as follows.
     *
     * The sides:
     *    U
     *  L F R B
     *    D
     *
     * Color wise:
     *
     *          W W W
     *          W W W
     *          W W W
     *
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *
     *          Y Y Y
     *          Y Y Y
     *          Y Y Y
    */


    // randomly shuffle a solved RubiksCube n number of times
    vector<MOVE> randomShuffleRubiksCube(int n);


    // tells color of a particular cell given the face, row, col
    virtual COLOR getColor(FACE face, int row, int col) const = 0;


    // sets color of a particular cell given the face, row, col to the given color
    virtual void setColor(FACE face, int row, int col, COLOR color) = 0;

    
    // Returns the first letter of the given COLOR
    static char getColorLetter(COLOR color);

    // Convert the move into string format
    static string getMove(MOVE move);

    // makes a particular move and then return the same RubiksCube object
    RubiksCube& move(MOVE m);

    // invert the given move or apply the inverse of the move
    RubiksCube& invert(MOVE m);

    /* 
      specific functions for moves
      they perform the operation and return the same RubiksCube object so 
      '&' sign is used to show the reference. This allows us to apply chaining
    */
    virtual RubiksCube& l() = 0;

    virtual RubiksCube& l_prime() = 0;

    virtual RubiksCube& l2() = 0;

    virtual RubiksCube& u() = 0;

    virtual RubiksCube& u_prime() = 0;

    virtual RubiksCube& u2() = 0;

    virtual RubiksCube& r() = 0;

    virtual RubiksCube& r_prime() = 0;

    virtual RubiksCube& r2() = 0;

    virtual RubiksCube& d() = 0;

    virtual RubiksCube& d_prime() = 0;

    virtual RubiksCube& d2() = 0;

    virtual RubiksCube& b() = 0;

    virtual RubiksCube& b_prime() = 0;

    virtual RubiksCube& b2() = 0;

    virtual RubiksCube& f() = 0;

    virtual RubiksCube& f_prime() = 0;

    virtual RubiksCube& f2() = 0;

    // returns a string of 3 colors present at a given corner position
    string getCornerColorString(uint8_t cornerPos) const;

    // returns which corner cubie (0 to 7) is present at a given corner position
    uint8_t getCornerIndex(uint8_t cornerPos) const;

    // returns the orientation (0 to 2) of the corner cubie present at the given corner position
    uint8_t getCornerOrientation(uint8_t cornerPos) const;
};