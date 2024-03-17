//
//  bishop.hpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#ifndef bishop_hpp
#define bishop_hpp

#include <stdio.h>

#include "piece.hpp"

uint64_t generatePseudoLegalBishopMovesFromSquare(int square, uint64_t occupancy);

class Bishop : public Piece{
public:
    Bishop(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;
    
};

#endif /* bishop_hpp */
