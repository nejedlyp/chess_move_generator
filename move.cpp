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
Move::Move(int from, int to, char promotion_piece){
    this->from = from;
    this->to = to;
    this->promotion_piece = promotion_piece;
    this->uci = IndexToSquare.at(from)+IndexToSquare.at(to)+promotion_piece;
}

Move::Move(std::string uci) {
    this->uci = uci;
    this->from = SquareToIndex.at(uci.substr(0,2));
    this->to = SquareToIndex.at(uci.substr(2,2));
    if (uci.size() == 5){
        this->promotion_piece = uci[4];
    }
}

string Move::get_uci() const {
    return this->uci;
}
