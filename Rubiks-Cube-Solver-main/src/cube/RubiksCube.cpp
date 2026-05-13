#include <bits/stdc++.h>

#include "RubiksCube.h"
using namespace std;

char RubiksCube::getColorLetter(COLOR color){
    switch(color){
        case COLOR::RED :
            return 'R';
        case COLOR::BLUE :
            return 'B';
        case COLOR::GREEN :
            return 'G';
        case COLOR::YELLOW :
            return 'Y';
        case COLOR::ORANGE :
            return 'O';
        case COLOR::WHITE :
            return 'W';
        default:
            return '?';
    }
}

void RubiksCube::print() const{
    cout << "Rubiks Cube : " << endl << endl;

    for(int row=0; row<3; row++){
        for (int i=0; i<7; i++) cout << " ";

        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
        }
        cout << " ";
        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
        }
        cout << " ";
        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
        }
        cout << " ";
        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int row=0; row<3; row++){
        for (int i=0; i<7; i++) cout << " ";

        for(int col=0; col<3; col++){
            cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffleRubiksCube(int n){
    vector<MOVE> moves;

    for(int i=0; i<n; i++){
        int ind = rand() % 18;
        MOVE randomMove = static_cast<MOVE>(ind);
        moves.push_back(randomMove);
        this->move(randomMove);
    }
    return moves;
}

RubiksCube& RubiksCube::move(MOVE m){
    switch(m){
        case MOVE::L : 
            return this->l();
        case MOVE::L_PRIME :
            return this->l_prime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::R_PRIME:
            return this->r_prime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::U_PRIME:
            return this->u_prime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::D_PRIME:
            return this->d_prime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::F_PRIME:
            return this->f_prime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::B_PRIME:
            return this->b_prime();
        case MOVE::B2:
            return this->b2();
        default:
            return *this;
    }
}

RubiksCube& RubiksCube::invert(MOVE m){
    switch(m){
        case MOVE::L : 
            return this->l_prime();
        case MOVE::L_PRIME :
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r_prime();
        case MOVE::R_PRIME:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u_prime();
        case MOVE::U_PRIME:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d_prime();
        case MOVE::D_PRIME:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f_prime();
        case MOVE::F_PRIME:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b_prime();
        case MOVE::B_PRIME:
            return this->b();
        case MOVE::B2:
            return this->b2();
        default:
            return *this;
    }
}

string RubiksCube::getMove(MOVE move){
    switch (move) {
        case MOVE::L:
            return "L";
        case MOVE::L_PRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::R_PRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::U_PRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::D_PRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::F_PRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::B_PRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
        default:
            return "?";
    }
}

/*
    | Corner No. | Position | Colors in solved state |
    | ---------- | -------- | ---------------------- |
    | 0          | ULF      | White, Green, Red      |
    | 1          | UFR      | White, Red, Blue       |
    | 2          | URB      | White, Blue, Orange    |
    | 3          | UBL      | White, Orange, Green   |
    | 4          | DLF      | Yellow, Green, Red     |
    | 5          | DFR      | Yellow, Red, Blue      |
    | 6          | DRB      | Yellow, Blue, Orange   |
    | 7          | DBL      | Yellow, Orange, Green  |
*/

string RubiksCube::getCornerColorString(uint8_t cornerPos) const{
    string str = "";
    switch (cornerPos){
        case 0:     // ULF
            str += getColorLetter(getColor(FACE::UP, 2, 0));
            str += getColorLetter(getColor(FACE::LEFT, 0, 2));
            str += getColorLetter(getColor(FACE::FRONT, 0, 0));
            break;
        case 1:     // UFR
            str += getColorLetter(getColor(FACE::UP, 2, 2));
            str += getColorLetter(getColor(FACE::FRONT, 0, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 0));
            break;
        case 2:     // URB
            str += getColorLetter(getColor(FACE::UP, 0, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 2));
            str += getColorLetter(getColor(FACE::BACK, 0, 0));
            break;
        case 3:     // UBL
            str += getColorLetter(getColor(FACE::UP, 0, 0));
            str += getColorLetter(getColor(FACE::BACK, 0, 2));
            str += getColorLetter(getColor(FACE::LEFT, 0, 0));
            break;
        case 4:     // DLF
            str += getColorLetter(getColor(FACE::DOWN, 0, 0));
            str += getColorLetter(getColor(FACE::LEFT, 2, 2));
            str += getColorLetter(getColor(FACE::FRONT, 2, 0));
            break;
        case 5:     // DFR
            str += getColorLetter(getColor(FACE::DOWN, 0, 2));
            str += getColorLetter(getColor(FACE::FRONT, 2, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 0));
            break;
        case 6:     // DRB
            str += getColorLetter(getColor(FACE::DOWN, 2, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 2));
            str += getColorLetter(getColor(FACE::BACK, 2, 0));
            break;
        case 7:     //DBL
            str += getColorLetter(getColor(FACE::DOWN, 2, 0));
            str += getColorLetter(getColor(FACE::BACK, 2, 2));
            str += getColorLetter(getColor(FACE::LEFT, 2, 0));
            break;
    }
    return str;
}

uint8_t RubiksCube::getCornerIndex(uint8_t cornerPos) const{
    string corner = getCornerColorString(cornerPos);
    sort(corner.begin(), corner.end());
    if(corner == "GRW")
        return 0;
    else if(corner == "BRW")
        return 1;
    else if(corner == "BOW")
        return 2;
    else if(corner == "GOW")
        return 3;
    else if(corner == "GRY")
        return 4;
    else if(corner == "BRY")
        return 5;
    else if(corner == "BOY")
        return 6;
    else           // "GOY"
        return 7;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t cornerPos) const{
    string corner = getCornerColorString(cornerPos);

    // Orientation is decided based on where the white/yellow sticker is

    if(cornerPos < 4){      // top layer
        if(corner[0] == 'W') return 0;      // 1st sticker
        if(corner[1] == 'W') return 1;      // 2nd sticker
        return 2;                           // 3rd sticker
    }
    else{                   // bottom layer
        if(corner[0] == 'Y') return 0;      // 1st sticker
        if(corner[1] == 'Y') return 1;      // 2nd sticker
        return 2;                           // 3rd sticker
    }
}