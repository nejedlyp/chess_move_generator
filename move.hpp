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
    Move(int from, int to);
    Move(string uci);
    string uci() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Move& obj) {
        return os << obj.uci();
    }
};

#endif /* move_hpp */
