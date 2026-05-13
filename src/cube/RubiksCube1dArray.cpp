#include<bits/stdc++.h>

#include "RubiksCube.h"
using namespace std;

class RubiksCube1dArray : public RubiksCube{

private:
    // return the index in 1D for given face, row, col
    static inline int getIndex(int face, int row, int col) {
        return (face * 9) + (row * 3) + col;
    }

    void rotateFace(int face){
        vector<char> temp(9);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i*3 + j] = cube[getIndex(face, i, j)];
            }
        }
        for(int i=2; i>=0; i--){
            for(int j=0; j<3; j++){
                cube[getIndex(face, j, 2-i)] = temp[i*3 + j];
            }
        }
    }

public:

    vector<char> cube;

    /*
    Solved Rubiks Cube
        Indexing of Faces
            Up → 0 (White)
            Left → 1 (Green)
            Front → 2 (Red)
            Right → 3 (Blue)
            Back → 4 (Orange)
            Down → 5 (Yellow)
    */

    // initialize the solved RubiksCube
    RubiksCube1dArray(){
        cube.resize(54);
        for(int face=0; face<6; face++){
            for(int row=0; row<3; row++){
                for(int col=0; col<3; col++){
                    cube[getIndex(face, row, col)] = getColorLetter(COLOR(face));
                }
            }
        }
    }

    // checking if it is solved or not
    bool isSolved() const override{
        for(int face=0; face<6; face++){
            for(int row=0; row<3; row++){
                for(int col=0; col<3; col++){
                    if(this->cube[getIndex(face, row, col)] != getColorLetter(COLOR(face))) return false;
                }
            }
        }
        return true;
    }

    COLOR getColor(FACE face, int row, int col) const override{
        int ind = static_cast<int>(face);
        char color = cube[getIndex(ind, row, col)];
        switch(color){
            case 'W':
                return COLOR::WHITE;
            case 'G':
                return COLOR::GREEN;
            case 'R':
                return COLOR::RED;
            case 'B':
                return COLOR::BLUE;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
        }
        return COLOR::UNKNOWN;
    }

    void setColor(FACE face, int row, int col, COLOR color) override{
        int ind = static_cast<int>(face);
        cube[getIndex(ind, row, col)] = getColorLetter(color);
    }

    RubiksCube& l() override{
        this->rotateFace(1);

        vector<char> frontStrip(3);
        for(int i=0; i<3; i++){
            frontStrip[i] = cube[getIndex(2, i, 0)];
        }

        for(int row=0; row<3; row++){
            // new 1st column of front = 1st column of upper
            cube[getIndex(2, row, 0)] = cube[getIndex(0, row, 0)];
        }
        for(int row=0; row<3; row++){
            // new 1st column of up = reverse of 3rd column of back
            cube[getIndex(0, row, 0)] = cube[getIndex(4, 2-row, 2)];
        }
        for(int row=0; row<3; row++){
            // new 3rd column of back = reverse of 1st column of down
            cube[getIndex(4, row, 2)] = cube[getIndex(5, 2-row, 0)];
        }
        for(int row=0; row<3; row++){
            // new 1st column of down = 1st column of front
            cube[getIndex(5, row, 0)] = frontStrip[row];
        }
        return *this;
    }

    RubiksCube& u() override{
        this->rotateFace(0);

        vector<char> frontStrip(3);
        for(int col=0; col<3; col++){
            frontStrip[col] = cube[getIndex(2, 0, col)];
        }

        for(int col=0; col<3; col++){
            // new 1st row of front = 1st row of right
            cube[getIndex(2, 0, col)] = cube[getIndex(3, 0, col)];
        }
        for(int col=0; col<3; col++){
            // new 1st row of right = 1st row of back
            cube[getIndex(3, 0, col)] = cube[getIndex(4, 0, col)];
        }
        for(int col=0; col<3; col++){
            // new 1st row of back = 1st row of left
            cube[getIndex(4, 0, col)] = cube[getIndex(1, 0, col)];
        }
        for(int col=0; col<3; col++){
            // new 1st row of left = 1st row of front
            cube[getIndex(1, 0, col)] = frontStrip[col];
        }
        return *this;
    }
    
    RubiksCube& r() override{
        this->rotateFace(3);

        vector<char> frontStrip(3);
        for(int i=0; i<3; i++){
            frontStrip[i] = cube[getIndex(2, i, 2)];
        }

        for(int row=0; row<3; row++){
            // new 3rd column of front = 3rd column of down
            cube[getIndex(2, row, 2)] = cube[getIndex(5, row, 2)];
        }
        for(int row=0; row<3; row++){
            // new 3rd column of down = reverse of 1st column of back
            cube[getIndex(5, row, 2)] = cube[getIndex(4, 2-row, 0)];
        }
        for(int row=0; row<3; row++){
            // new 1st column of back = reverse of 3rd column of up
            cube[getIndex(4, row, 0)] = cube[getIndex(0, 2-row, 2)];
        }
        for(int row=0; row<3; row++){
            // new 3rd column of up = 3rd column of front
            cube[getIndex(0, row, 2)] = frontStrip[row];
        }
        return *this;
    }
    
    RubiksCube& d() override{
        this->rotateFace(5);
        
        vector<char> frontStrip(3);
        for(int col=0; col<3; col++){
            frontStrip[col] = cube[getIndex(2, 2, col)];
        }

        for(int col=0; col<3; col++){
            // new 3rd row of front = 3rd row of left
            cube[getIndex(2, 2, col)] = cube[getIndex(1, 2, col)];
        }
        for(int col=0; col<3; col++){
            // new 3rd row of left = 3rd row of back
            cube[getIndex(1, 2, col)] = cube[getIndex(4, 2, col)];
        }
        for(int col=0; col<3; col++){
            // new 3rd row of back = 3rd row of right
            cube[getIndex(4, 2, col)] = cube[getIndex(3, 2, col)];
        }
        for(int col=0; col<3; col++){
            // new 3rd row of right = 3rd row of front
            cube[getIndex(3, 2, col)] = frontStrip[col];
        }
        return *this;
    }

    RubiksCube& b() override{
        this->rotateFace(4);

        vector<char> upStrip(3);
        for(int i=0; i<3; i++){
            upStrip[i] = cube[getIndex(0, 0, i)];
        }

        for(int i=0; i<3; i++){
            // new 1st row of up = 3rd column of right
            cube[getIndex(0, 0, i)] = cube[getIndex(3, i, 2)];
        }
        for(int i=0; i<3; i++){
            // new 3rd column of right = reverse of 3rd row of down
            cube[getIndex(3, i, 2)] = cube[getIndex(5, 2, 2-i)];
        }
        for(int i=0; i<3; i++){
            // new 3rd row of down = 1st column of left
            cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
        }
        for(int i=0; i<3; i++){
            // new 1st column of left = reverse of 1st row of top
            cube[getIndex(1, i, 0)] = upStrip[2-i];
        }
        return *this;
    }
    
    RubiksCube& f() override{
        this->rotateFace(2);

        vector<char> upStrip(3);
        for(int i=0; i<3; i++){
            upStrip[i] = cube[getIndex(0, 2, i)];
        }

        for(int i=0; i<3; i++){
            // new 3rd row of up = reverse of 3rd column of left
            cube[getIndex(0, 2, i)] = cube[getIndex(1, 2-i, 2)];
        }
        for(int i=0; i<3; i++){
            // new 3rd column of left = 1st row of down
            cube[getIndex(1, i, 2)] = cube[getIndex(5, 0, i)];
        }
        for(int i=0; i<3; i++){
            // new 1st row of down = reverse of 1st column of right
            cube[getIndex(5, 0, i)] = cube[getIndex(3, 2-i, 0)];
        }
        for(int i=0; i<3; i++){
            // new 1st column of right = 3rd row of up
            cube[getIndex(3, i, 0)] = upStrip[i];
        }
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

    bool operator==(const RubiksCube1dArray &r2) const{
        for(int i=0; i<54; i++){
            if(cube[i] != r2.cube[i]) return false;
        }
        return true;
    }

    RubiksCube1dArray& operator=(const RubiksCube1dArray& r){
        for(int i=0; i<54; i++){
            cube[i] = r.cube[i];
        }
        return *this;
    }
};

struct Hash1dArray{
    size_t operator()(const RubiksCube1dArray &r) const{
        string str;
        for(int i=0; i<54; i++) str += r.cube[i];
        return hash<string>()(str);
    }
};