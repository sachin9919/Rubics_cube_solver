#include <bits/stdc++.h>

#include "RubiksCube.h"
using namespace std;

class RubiksCubeBitboard : public RubiksCube{
private:

    // stores the position of the cell given (row, col)
    static constexpr int cellIndex[3][3] = {
        {0, 1, 2},
        {7, 8, 3},
        {6, 5, 4}
    };

    static constexpr uint64_t ONE_8 = (1ULL << 8) - 1;
    
    // generates the solved configuration of a given face
    static uint64_t getSolvedFace(int face){
        uint64_t color = 1 << face;
        uint64_t val = 0;
        for(int i=0; i<8; i++){
            val = (val << 8) | color;
        }
        return val;
    }

    void rotateFace(int face){
        uint64_t front_16 = cube[face] >> (8*6);
        cube[face] = (cube[face] << 16) | front_16;
    }

    // replace a row/col of face f1 with row/col of face f2
    void replaceStrip(int f1, int c11, int c12, int c13, int f2, int c21, int c22, int c23){
        uint64_t newColor1 = getColorBits(f2, c21);
        uint64_t newColor2 = getColorBits(f2, c22);
        uint64_t newColor3 = getColorBits(f2, c23);

        setColorBits(f1, c11, newColor1);
        setColorBits(f1, c12, newColor2);
        setColorBits(f1, c13, newColor3);
    }

    // return the color in binary for a given face, pos(0, 7)
    uint64_t getColorBits(int face, int pos) const{
        return (cube[face] >> (8 * pos)) & ONE_8;
    }

    // sets the color for a given face, pos(0, 7)
    void setColorBits(int face, int pos, uint64_t color){
        cube[face] = (cube[face] & (~(ONE_8 << (8 * pos)))) | (color << (8 * pos));
    }

public:

    // White 	00000001
    // Green 	00000010
    // Red 	    00000100
    // Blue 	00001000
    // Orange 	00010000
    // Yellow 	00100000
    
    // UP, LEFT, FRONT, RIGHT, BACK, DOWN
    uint64_t cube[6];   // 6 faces(8 colors each of 8 bits)

    RubiksCubeBitboard(){
        for(int face=0; face<6; face++){
            cube[face] = getSolvedFace(face);
        }
    }

    bool isSolved() const override{
        for(int face=0; face<6; face++){
            if(cube[face] != getSolvedFace(face)) return false;
        }
        return true;
    }

    COLOR getColor(FACE face, int row, int col) const override{
        int faceInd = static_cast<int>(face);
        int pos = cellIndex[row][col];

        if(pos == 8) return COLOR(faceInd);
        
        uint64_t f = cube[faceInd];
        f = f >> (8 * pos);
        f = f & ONE_8;

        for(int i=0; i<8; i++){
            if((f >> i) & 1) return COLOR(i);
        }
        return COLOR::UNKNOWN;
    }

    void setColor(FACE face, int row, int col, COLOR color) override{
        int faceInd = static_cast<int>(face);
        int pos = cellIndex[row][col];
        if(pos == 8) return;

        int clr = static_cast<int>(color);
        uint64_t newColor = 1 << clr;

        cube[faceInd] &= ~(ONE_8 << (8 * pos));
        cube[faceInd] |= (newColor << (8 * pos));
    }

    RubiksCube& u() override{
        this->rotateFace(0);

        uint64_t clr1 = getColorBits(2, 0);
        uint64_t clr2 = getColorBits(2, 1);
        uint64_t clr3 = getColorBits(2, 2);

        // new 1st row of front = 1st row of right
        replaceStrip(2, 0, 1, 2, 3, 0, 1, 2);

        // new 1st row of right = 1st row of back
        replaceStrip(3, 0, 1, 2, 4, 0, 1, 2);

        // new 1st row of back = 1st row of left
        replaceStrip(4, 0, 1, 2, 1, 0, 1, 2);

        // new 1st row of left = 1st row of front
        setColorBits(1, 0, clr1);
        setColorBits(1, 1, clr2);
        setColorBits(1, 2, clr3);

        return *this;
    }

    RubiksCube& l() override{
        this->rotateFace(1);

        uint64_t clr1 = getColorBits(2, 0);
        uint64_t clr2 = getColorBits(2, 7);
        uint64_t clr3 = getColorBits(2, 6);

        // new 1st column of front = 1st column of upper
        replaceStrip(2, 0, 7, 6, 0, 0, 7, 6);

        // new 1st column of up = reverse of 3rd column of back
        replaceStrip(0, 0, 7, 6, 4, 4, 3, 2);

        // new 3rd column of back = reverse of 1st column of down
        replaceStrip(4, 2, 3, 4, 5, 6, 7, 0);

        // new 1st column of down = 1st column of front
        setColorBits(5, 0, clr1);
        setColorBits(5, 7, clr2);
        setColorBits(5, 6, clr3);
        
        return *this;
    }
    
    RubiksCube& f() override{
        this->rotateFace(2);

        uint64_t clr1 = getColorBits(0, 6);
        uint64_t clr2 = getColorBits(0, 5);
        uint64_t clr3 = getColorBits(0, 4);

        // new 3rd row of up = reverse of 3rd column of left
        replaceStrip(0, 6, 5, 4, 1, 4, 3, 2);
        
        // new 3rd column of left = 1st row of down
        replaceStrip(1, 2, 3, 4, 5, 0, 1, 2);

        // new 1st row of down = reverse of 1st column of right
        replaceStrip(5, 0, 1, 2, 3, 6, 7, 0);

        // new 1st column of right = 3rd row of up
        setColorBits(3, 0, clr1);
        setColorBits(3, 7, clr2);
        setColorBits(3, 6, clr3);

        return *this;
    }

    RubiksCube& r() override{
        this->rotateFace(3);

        uint64_t clr1 = getColorBits(2, 2);
        uint64_t clr2 = getColorBits(2, 3);
        uint64_t clr3 = getColorBits(2, 4);

        // new 3rd column of front = 3rd column of down
        replaceStrip(2, 2, 3, 4, 5, 2, 3, 4);
        
        // new 3rd column of down = reverse of 1st column of back
        replaceStrip(5, 2, 3, 4, 4, 6, 7, 0);

        // new 1st column of back = reverse of 3rd column of up
        replaceStrip(4, 0, 7, 6, 0, 4, 3, 2);

        // new 3rd column of up = 3rd column of front
        setColorBits(0, 2, clr1);
        setColorBits(0, 3, clr2);
        setColorBits(0, 4, clr3);

        return *this;
    }
    
    
    RubiksCube& b() override{
        this->rotateFace(4);

        uint64_t clr1 = getColorBits(0, 0);
        uint64_t clr2 = getColorBits(0, 1);
        uint64_t clr3 = getColorBits(0, 2);

        // new 1st row of up = 3rd column of right
        replaceStrip(0, 0, 1, 2, 3, 2, 3, 4);
        
        // new 3rd column of right = reverse of 3rd row of down
        replaceStrip(3, 2, 3, 4, 5, 4, 5, 6);

        // new 3rd row of down = 1st column of left
        replaceStrip(5, 6, 5, 4, 1, 0, 7, 6);

        // new 1st column of left = reverse of 1st row of top
        setColorBits(1, 0, clr3);
        setColorBits(1, 7, clr2);
        setColorBits(1, 6, clr1);

        return *this;
    }
    
    RubiksCube& d() override{
        this->rotateFace(5);

        uint64_t clr1 = getColorBits(2, 6);
        uint64_t clr2 = getColorBits(2, 5);
        uint64_t clr3 = getColorBits(2, 4);

        // new 3rd row of front = 3rd row of left
        replaceStrip(2, 6, 5, 4, 1, 6, 5, 4);
        
        // new 3rd row of left = 3rd row of back
        replaceStrip(1, 6, 5, 4, 4, 6, 5, 4);

        // new 3rd row of back = 3rd row of right
        replaceStrip(4, 6, 5, 4, 3, 6, 5, 4);

        // new 3rd row of right = 3rd row of front
        setColorBits(3, 6, clr1);
        setColorBits(3, 5, clr2);
        setColorBits(3, 4, clr3);

        return *this;
    }


    RubiksCube& l_prime() override{
        this->l();
        this->l();
        this->l();

        return *this;
    }

    RubiksCube& l2() override{
        this->l();
        this->l();

        return *this;
    }

    RubiksCube& u_prime() override{
        this->u();
        this->u();
        this->u();

        return *this;
    }

    RubiksCube& u2() override{
        this->u();
        this->u();

        return *this;
    }

    RubiksCube& r_prime() override{
        this->r();
        this->r();
        this->r();

        return *this;
    }
    
    RubiksCube& r2() override{
        this->r();
        this->r();

        return *this;
    }

    RubiksCube& d_prime() override{
        this->d();
        this->d();
        this->d();

        return *this;
    }

    RubiksCube& d2() override{
        this->d();
        this->d();

        return *this;
    }

    RubiksCube& b_prime() override{
        this->b();
        this->b();
        this->b();

        return *this;
    }

    RubiksCube& b2() override{
        this->b();
        this->b();

        return *this;
    }


    RubiksCube& f_prime() override{
        this->f();
        this->f();
        this->f();

        return *this;
    }

    RubiksCube& f2() override{
        this->f();
        this->f();

        return *this;
    }

    bool operator==(const RubiksCubeBitboard &r2) const{
        for(int i=0; i<6; i++){
            if(cube[i] != r2.cube[i]) return false;
        }
        return true;
    }

    RubiksCubeBitboard& operator=(const RubiksCubeBitboard &r){
        for(int i=0; i<6; i++){
            cube[i] = r.cube[i];
        }
        return *this;
    }
};

struct HashBitboard{
    size_t operator()(const RubiksCubeBitboard &r) const{
        uint64_t hashedVal = r.cube[0];
        for(int i=1; i<6; i++){
            hashedVal = hashedVal ^ r.cube[i];
        }
        return (size_t)hashedVal;
    }
};