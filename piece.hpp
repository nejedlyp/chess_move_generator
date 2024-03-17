//
//  piece.h
//  Engine
//
//  Created by Petr on 09.03.2024.
//


#ifndef piece_h
#define piece_h

#include "string"
#include <iostream>
#include <cctype>
#include "vector"
#include "move.hpp"
using namespace std;

class Bitboards;

class Piece{
public:
    char type;
    int index;
    uint64_t bitboard;
    bool color;
    Piece(char type, int square_idx);
    bool slider;
    
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) = 0;
    
    virtual void get_uci(Bitboards* bb, vector<Move>& moves);

    
};

uint64_t getBitboardRay(int square_1_idx, int square_2_idx);
void print_bitboard(uint64_t bb);
//void print_bitboard(Piece p);
void print_bitboard(Piece* p);

vector<int> bitboard2index(uint64_t value);
#endif /* piece_h */
