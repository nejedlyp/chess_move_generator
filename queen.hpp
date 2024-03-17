//
//  queen.hpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#ifndef queen_hpp
#define queen_hpp

#include <stdio.h>
#include "piece.hpp"

uint64_t generatePseudoLegalQueenMovesFromSquare(int square, uint64_t occupancy);

class Queen : public Piece{
public:
    Queen(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;
    
};
#endif /* queen_hpp */
