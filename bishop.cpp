//
//  bishop.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#include "bishop.hpp"

uint64_t generatePseudoLegalBishopMovesFromSquare(int square, uint64_t occupancy){
    uint64_t moves = 0; // Bitboard for moves, initially empty

    // Directions: up-right, up-left, down-right, down-left
    int directions[4] = {7, 9, -7, -9};

    for (int direction : directions) {
        for (int n = 1; n < 8; ++n) {
            int target_square = square + direction * n;

            // Check if off the board
            if (target_square < 0 || target_square >= 64) {
                break;
            }

            // Calculate original and target ranks and files
            int original_rank = square / 8;
            int original_file = square % 8;
            int target_rank = target_square / 8;
            int target_file = target_square % 8;

            // Check for wrapping to prevent illegal moves
            if (abs(original_rank - target_rank) != abs(original_file - target_file)) {
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




Bishop::Bishop(bool color, int square_index) : Piece(color ? 'B':'b', square_index){};


uint64_t Bishop::get_attack_bitboard(uint64_t occupancy){
    return generatePseudoLegalBishopMovesFromSquare(this->index, occupancy);
}
