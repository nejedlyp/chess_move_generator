//
//  rook.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#include "rook.hpp"

uint64_t generatePseudoLegalRookMovesFromSquare(int square, uint64_t occupancy){
    uint64_t moves = 0; // Bitboard for moves, initially empty

    // Directions: right, left, up, down
    int directions[4] = {1, -1, 8, -8};

    for (int direction : directions) {
        for (int n = 1; n < 8; ++n) {
            int target_square = square + direction * n;

            // Check if off the board
            if (target_square < 0 || target_square >= 64) {
                break;
            }
            // Check for wrapping
            if ((direction == 1 || direction == -1) && (target_square / 8) != (square / 8)) {
                break;
            }

            // Add move
            moves |= 1ULL << target_square;

            // Stop if a blocker is encountered
            if (occupancy & (1ULL << target_square)) {
                break;
            }
        }
    }

    return moves;
}



Rook::Rook(bool color, int square_index) : Piece(color ? 'R':'r', square_index){};


uint64_t Rook::get_attack_bitboard(uint64_t occupancy){
    return generatePseudoLegalRookMovesFromSquare(this->index, occupancy);
}
