//
//  king.hpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#ifndef king_hpp
#define king_hpp

#include <stdio.h>
#include "piece.hpp"
#include "bitboards.hpp"
#include "vector"
#include "move.hpp"
#include "queen.hpp"

uint64_t generatePseudoLegalKingMovesFromSquare(int square, uint64_t occupancy);

class King : public Piece{
public:
    King(bool color, int square_index);
    virtual uint64_t get_attack_bitboard(uint64_t occupancy) override;
    
    vector<Piece*> get_checking_pieces(vector<Piece*> pieces, Bitboards* bb);
    vector<Move> get_pinned_moves(vector<Piece*> pieces, Bitboards* bb);

    virtual void get_uci(Bitboards* bb, vector<Move>& moves) override;
};
#endif /* king_hpp */
