//
//  bitboards.hpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#ifndef bitboards_hpp
#define bitboards_hpp

#include <stdio.h>
#include "vector"
#include "piece.hpp"

using namespace std;

class Bitboards{
public:
    uint64_t wk = 0;
    uint64_t bk = 0;

    uint64_t occupancy = 0;
    uint64_t occupancy_white = 0;
    uint64_t occupancy_black = 0;
    uint64_t occupancy_no_wk = 0;
    uint64_t occupancy_no_bk = 0;
    
    uint64_t attack_white = 0;
    uint64_t attack_black = 0;
    
    uint64_t attack_white_no_bk = 0;
    uint64_t attack_black_no_wk = 0;
    
    Bitboards(vector<Piece*> pieces);
    Bitboards();
};

#endif /* bitboards_hpp */
