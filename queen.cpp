//
//  queen.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"

uint64_t generatePseudoLegalQueenMovesFromSquare(int square, uint64_t occupancy){
    return generatePseudoLegalBishopMovesFromSquare(square, occupancy) | generatePseudoLegalRookMovesFromSquare(square, occupancy);
};

Queen::Queen(bool color, int square_index) : Piece(color ? 'Q':'q', square_index){};


uint64_t Queen::get_attack_bitboard(uint64_t occupancy){
    return generatePseudoLegalQueenMovesFromSquare(this->index, occupancy);
}
