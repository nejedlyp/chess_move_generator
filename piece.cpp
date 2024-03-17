//
//  piece.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//
#include "piece.hpp"
#include <stdio.h>
#include "bitboards.hpp"

class Bitboards;


Piece::Piece(char type, int square_idx){
    this->type = type;
    this->index = square_idx;
    this->bitboard = 1ULL << this->index;
    this->color = isupper(this->type);
    // check if the piece type is a slider
    this->slider = (this->type == 'B' ||
                    this->type == 'R' ||
                    this->type == 'Q' ||
                    this->type == 'b' ||
                    this->type == 'r' ||
                    this->type == 'q');
    
}


void print_bitboard(uint64_t bb){
    for (int r=0; r<8; r++){
        for (int c=0; c<8; c++){
            int square = 63 - (r * 8 + c);
            if (bb & (1ULL << square)){
                cout<<1;
            }
            else{
                cout<<".";
            }
            cout<<" ";
        }
        cout<<"\n";
    }
    cout << "\n";
}

//void print_bitboard(Piece p){
//    print_bitboard(p.bitboard);
//}

void print_bitboard(Piece* p){
    print_bitboard(p->bitboard);
}


vector<int> bitboard2index(uint64_t value) {
    vector<int> positions;
    for (int pos = 0; value != 0; ++pos) {
        if (value & 1) { // Check if the LSB is set
            positions.push_back(pos);
        }
        value >>= 1; // Shift the value to the right by 1
    }
    return positions;
}

void Piece::get_uci(Bitboards* bb, vector<Move>& moves){
    uint64_t friends_occupancy_bitboard = this->color ? bb->occupancy_white:bb->occupancy_black;
    
    uint64_t move_bitboard = this->get_attack_bitboard(bb->occupancy) & ~friends_occupancy_bitboard;
    
    for (const auto& k: bitboard2index(move_bitboard)){
        moves.push_back(Move(this->index, k));
    }
};


uint64_t getBitboardRay(int square_1_idx, int square_2_idx) {
    uint64_t bitboard = 0;
    bool direction_found = false;

    std::vector<int> directions = {-9, -8, -7, -1, 1, 7, 8, 9};

    for (int direction : directions) {
        uint64_t temp_bitboard = 0;
        int square = square_1_idx;
        while (square >= 0 && square <= 63) {
            temp_bitboard |= uint64_t(1) << square;
            if (square == square_2_idx) {
                bitboard |= temp_bitboard;
                direction_found = true;
                break;
            }
            if ((square % 8 == 0 && (direction == -9 || direction == -1 || direction == 7)) ||
                (square % 8 == 7 && (direction == -7 || direction == 1 || direction == 9))) {
                break;
            }
            square += direction;
        }

        if (direction_found) {
            break;
        }
    }
    return bitboard;
}
