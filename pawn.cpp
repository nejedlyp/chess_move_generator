//
//  pawn.cpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#include "pawn.hpp"



// Assuming a function or mechanism to convert square notation to bitboard index is provided elsewhere
// For example: int squareToIndex(std::string square);

uint64_t generatePseudolegalWhitePawnCapturesFromSquare(int square) {
    // Convert the input square to a bitboard position
    uint64_t squareBit = 1ULL << square; // Assuming square is already an index 0-63

    return ((squareBit << 9) & NOT_H_FILE) | ((squareBit << 7) & NOT_A_FILE);
}

uint64_t generateWhitePawnPushesFromSquare(int square, uint64_t blockers) {
    const uint64_t rank_2_mask = 0x0000000000FF00; // Bitboard mask for rank 2
    uint64_t squareBit = 1ULL << square; // Convert square index to bitboard

    uint64_t singlePush = (squareBit << 8) & ~blockers; // Single square forward push

    uint64_t doublePush = 0;
    if (squareBit & rank_2_mask) {
        // Check for double push: pawn is on rank 2 and the square in front is not blocked
        doublePush = (squareBit << 16) & ~blockers & ~(blockers << 8);
    }

    return singlePush | doublePush; // Combine single and double pushes
}


uint64_t generatePseudolegalBlackPawnCapturesFromSquare(int square) {
    uint64_t squareBit = 1ULL << square; // Assuming square is already an index 0-63

    return ((squareBit >> 7) & NOT_H_FILE) | ((squareBit >> 9) & NOT_A_FILE);
}

uint64_t generateBlackPawnPushesFromSquare(int square, uint64_t blockers) {
    const uint64_t rank_7_mask = 0x00FF000000000000; // Bitboard mask for rank 7
    uint64_t squareBit = uint64_t(1) << square; // Convert square index to bitboard

    uint64_t singlePush = (squareBit >> 8) & ~blockers; // Single square forward push

    uint64_t doublePush = 0;
    if (squareBit & rank_7_mask) {
        // Check for double push: pawn is on rank 7 and the square in front is not blocked
        doublePush = (squareBit >> 16) & ~blockers & ~(blockers >> 8);
    }

    return singlePush | doublePush; // Combine single and double pushes
}


Pawn::Pawn(bool color, int square_index) : Piece(color ? 'P':'p', square_index){};


uint64_t Pawn::get_attack_bitboard(uint64_t occupancy){
    if (this->color){
        return generatePseudolegalWhitePawnCapturesFromSquare(this->index);
    }else{
        return generatePseudolegalBlackPawnCapturesFromSquare(this->index);
    }
}

uint64_t Pawn::get_push_bitboard(uint64_t occupancy){
    if (this->color){
        return generateWhitePawnPushesFromSquare(this->index,occupancy);
    }else{
        return generateBlackPawnPushesFromSquare(this->index,occupancy);
    }
}


void Pawn::get_uci(Bitboards* bb, vector<Move>& moves){
    uint64_t oponents_occupancy_bitboard = this->color ? bb->occupancy_black:bb->occupancy_white;
    
    uint64_t captures_bitboard = this->get_attack_bitboard(bb->occupancy) & oponents_occupancy_bitboard & this->pin_attack_filter & this->check_attack_filter;
    //print_bitboard(captures_bitboard);
    uint64_t push_bitboard = this->get_push_bitboard(bb->occupancy) & this->pin_attack_filter & this->check_attack_filter;
    
    for (const auto& k: bitboard2index(captures_bitboard)){
        moves.push_back(Move(this->index, k));
    }
    for (const auto& k: bitboard2index(push_bitboard)){
        moves.push_back(Move(this->index, k));
    }

}
