//
//  bitboards.cpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#include "bitboards.hpp"

Bitboards::Bitboards(){
    
}


Bitboards::Bitboards(vector<Piece*> pieces){
    for (const auto& p: pieces){
        occupancy |= p->bitboard;
        
        if (p->color){
            occupancy_white |= p->bitboard;
        }
        else{
            occupancy_black |= p->bitboard;
        }
        
        if (p->type == 'K'){
            wk |= p->bitboard;
        }
        if (p->type == 'k'){
            bk |= p->bitboard;
        }
    }
    occupancy_no_bk = occupancy ^ bk;
    occupancy_no_wk = occupancy ^ wk;
    
    for (const auto& p: pieces){
        if (p->color){
            attack_white |= p->get_attack_bitboard(occupancy);
            attack_white_no_bk |= p->get_attack_bitboard(occupancy_no_bk);
        }
        else{
            attack_black |= p->get_attack_bitboard(occupancy);
            attack_black_no_wk |= p->get_attack_bitboard(occupancy_no_wk);
        }
    }
}
