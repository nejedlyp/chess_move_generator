//
//  king.cpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#include "king.hpp"

uint64_t generatePseudoLegalKingMovesFromSquare(int square, uint64_t occupancy){
    // Convert the input square if necessary, depending on your board representation
    // int squareIndex = squares.indexOf(square); // This line should be adapted to your needs

    uint64_t moves = 0; // Bitboard for moves, initially empty

    // Directions: up, down, left, right, up-right, up-left, down-right, down-left
    int directions[8] = {8, -8, 1, -1, 9, 7, -9, -7};

    for (int direction : directions) {
        int targetSquare = square + direction;

        // Check if off the board
        if (targetSquare < 0 || targetSquare >= 64) continue;

        // Calculate original and target ranks and files
        int originalRank = square / 8;
        int originalFile = square % 8;
        int targetRank = targetSquare / 8;
        int targetFile = targetSquare % 8;

        // Check for wrapping to prevent illegal moves
        if (abs(originalRank - targetRank) > 1 || abs(originalFile - targetFile) > 1) continue;

        // Add move
        moves |= (uint64_t)1 << targetSquare;
    }
    return moves;
};

King::King(bool color, int square_index) : Piece(color ? 'K':'k', square_index){};


void King::find_checks(vector<Piece*> friends, vector<Piece*> opponents, Bitboards* bb){
    uint64_t tmp = 0xFFFFFFFFFFFFFFFF;
    for (const auto& p: opponents){
        if (p->get_attack_bitboard(bb->occupancy) & this->bitboard){
            tmp &= BITBOARD_RAY_MAP.at(make_pair(this->index,p->index));
        }
    }
    for (auto& k: friends){
        k->check_attack_filter = tmp;
    }
}

void King::get_uci(Bitboards* bb, vector<Move>& moves){
    uint64_t friends_occupancy_bitboard = this->color ? bb->occupancy_no_wk:bb->occupancy_no_bk;
    uint64_t enemies_attacks_bitboard = this->color? bb->attack_black_no_wk:bb->attack_white_no_bk;
    
    uint64_t move_bitboard = this->get_attack_bitboard(0) & ~friends_occupancy_bitboard & ~enemies_attacks_bitboard;
    
    for (const auto& k: bitboard2index(move_bitboard)){
        moves.push_back(Move(this->index, k));
    }
};



uint64_t King::get_attack_bitboard(uint64_t occupancy){
    return generatePseudoLegalKingMovesFromSquare(this->index, occupancy);
}

void King::find_pins(vector<Piece*> friends, vector<Piece*> opponents, Bitboards* bb){
    uint64_t friends_occupancy_bitboard = this->color ? bb->occupancy_white:bb->occupancy_black;

    vector<Move> output = vector<Move>();
    for (const auto& p: opponents){
        if (!p->slider){
            continue;
        }
        uint64_t tmp = ~p->bitboard &
                        p->get_attack_bitboard(bb->occupancy) &
                       ~this->bitboard &
                        generatePseudoLegalQueenMovesFromSquare(this->index,bb->occupancy) &
                       BITBOARD_RAY_MAP.at(make_pair(this->index,p->index)) &
                       friends_occupancy_bitboard;

        if (tmp == 0){
            continue;
        }

        //int from_square = bitboard2index(tmp)[0];
        print_bitboard(tmp);
        uint64_t to_squares = BITBOARD_RAY_MAP.at(make_pair(this->index,p->index)) & ~this->bitboard & ~tmp;
        print_bitboard(to_squares);
        for (auto& k: friends){
            if (tmp == k->bitboard){
                k->pin_attack_filter = to_squares;
                auto stop = 1;
            }
        }
    }
}
