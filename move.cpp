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

Move::Move(std::string uci) {
    this->from = SquareToIndex.at(uci.substr(0,2));
    this->to = SquareToIndex.at(uci.substr(2,2));
}

string Move::uci() const {
    return IndexToSquare.at(this->from)+IndexToSquare.at(this->to);
}
