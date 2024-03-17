//
//  knight.hpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#ifndef knight_hpp
#define knight_hpp
#include "piece.hpp"
#include <stdio.h>
#include "bitboards.hpp"

uint64_t generatePseudoLegalKnightMovesFromSquare(int square);

class Knight : public Piece{
public:
    Knight(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;
    
};

#endif /* knight_hpp */
