//
//  pawn.hpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#ifndef pawn_hpp
#define pawn_hpp

#include <stdio.h>
#include "piece.hpp"
#include "bitboards.hpp"
const uint64_t NOT_A_FILE = 0x7F7F7F7F7F7F7F7F;
const uint64_t NOT_H_FILE = 0xFEFEFEFEFEFEFEFE;

uint64_t generatePseudolegalWhitePawnCapturesFromSquare(int square);
uint64_t generateWhitePawnPushesFromSquare(int square, uint64_t blockers);

uint64_t generatePseudolegalBlackPawnCapturesFromSquare(int square);
uint64_t generateBlackPawnPushesFromSquare(int square, uint64_t blockers);

class Pawn : public Piece{
public:
    Pawn(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;
    virtual void get_uci(Bitboards* bb, vector<Move>& moves) override;
    uint64_t get_push_bitboard(uint64_t occupancy);
    
};


#endif /* pawn_hpp */
