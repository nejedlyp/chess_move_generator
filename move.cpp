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
    this->uci = IndexToSquare.at(from)+IndexToSquare.at(to);
}

Move::Move(std::string uci) {
    this->uci = uci;
    this->from = SquareToIndex.at(uci.substr(0,2));
    this->to = SquareToIndex.at(uci.substr(2,2));
}

string Move::get_uci() const {
    return this->uci;
}
