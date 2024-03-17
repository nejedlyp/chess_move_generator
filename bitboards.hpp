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
#include "map"

using namespace std;

// Function to generate the map
static map<std::pair<int, int>, uint64_t> generateRayMap() {
    map<std::pair<int, int>, uint64_t> rayMap;
    for (int sq1 = 0; sq1 < 64; ++sq1) {
        for (int sq2 = 0; sq2 < 64; ++sq2) {
            rayMap[std::make_pair(sq1, sq2)] = getBitboardRay(sq1, sq2);
        }
    }
    return rayMap;
}

// The static const map
const std::map<std::pair<int, int>, uint64_t> BITBOARD_RAY_MAP = generateRayMap();



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
