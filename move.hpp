//
//  move.hpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#ifndef move_hpp
#define move_hpp

#include <stdio.h>
#include "square_map.h"
#include "string"
using namespace std;

class Move{
public:
    int from;
    int to;
    char piece;
    bool is_capture = false;
    bool is_promotion = false;
    char promotion_piece = 0;
    bool is_en_passant = false;
    bool is_castling = false;
    bool is_double_push = false;
    bool is_push = false;
    bool is_check = false;
    string uci;

    Move(char piece, int from, int to);
    Move(char piece, int from, int to, char promotion_piece);

    Move(string uci);
    string get_uci() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Move& obj) {
        return os << obj.get_uci();
    }
};

#endif /* move_hpp */
