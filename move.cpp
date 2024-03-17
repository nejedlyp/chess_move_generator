//
//  move.cpp
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#include "move.hpp"

Move::Move(int from, int to){
    this->from = from;
    this->to = to;
}

string Move::uci() const {
    return IndexToSquare.at(this->from)+IndexToSquare.at(this->to);
}
