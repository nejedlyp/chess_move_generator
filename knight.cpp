//
//  knight.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//

#include "knight.hpp"



uint64_t generatePseudoLegalKnightMovesFromSquare(int square) {
    uint64_t moves = 0ULL; // Bitboard for moves, initially empty

    // Directions: up-right, up-left, right-up, right-down, down-right, down-left, left-up, left-down
    int directions[8] = {6, 10, 15, 17, -6, -10, -15, -17};

    for (int direction : directions) {
        int target_square = square + direction;

        // Check if off the board
        if (target_square < 0 || target_square >= 64) continue;

        // Calculate original and target ranks and files
        int original_rank = square / 8;
        int original_file = square % 8;
        int target_rank = target_square / 8;
        int target_file = target_square % 8;

        // Check for wrapping to prevent illegal moves
        if (abs(original_rank - target_rank) > 2 || abs(original_file - target_file) > 2) continue;

        // Add move
        moves |= 1ULL << target_square;
    }

    return moves;
}

Knight::Knight(bool color, int square_index) : Piece(color ? 'N':'n', square_index){};


uint64_t Knight::get_attack_bitboard(uint64_t occupancy)
{
    return generatePseudoLegalKnightMovesFromSquare(this->index);
}
