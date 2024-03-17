//
//  rook.hpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#ifndef rook_hpp
#define rook_hpp

#include <stdio.h>
#include "piece.hpp"
#include "bitboards.hpp"

uint64_t generatePseudoLegalRookMovesFromSquare(int square, uint64_t occupancy);

class Rook : public Piece{
public:
    Rook(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;

};

#endif /* rook_hpp */
