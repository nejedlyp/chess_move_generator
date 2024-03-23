//
// Created by Petr on 23.03.2024.
//

#ifndef ENGINE_BOARD_H
#define ENGINE_BOARD_H
#include "string"
#include "piece.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "vector"
#include "king.hpp"
#include "pawn.hpp"
#include "sstream"
#include "square_map.h"
#include "bitboards.hpp"
#include "move.hpp"
#include <algorithm>
#include <map>


class Board{
public:
    Board(const string& fen);
//    ~Board(){
//        for (auto &p: pieces){
//            delete p;
//        }
//    }

    vector<Move> get_legal_moves();
    vector<string> get_legal_moves_uci();

    string get_fen() const;

    void show() const;
    void push_move(Move m);

    Board deep_copy() const;

private:
    bool active_color;
    bool castling_K;
    bool castling_k;
    bool castling_Q;
    bool castling_q;
    string enPassant_square;
    int halfMoveClock;
    int fullMoveNumber;

    Bitboards bitboards;

    vector<Piece*> pieces;
    vector<Piece*> pieces_white;
    vector<Piece*> pieces_black;

    King* wk = nullptr;
    King* bk = nullptr;

    map<int,Piece*> square_piece_map;


    string fen;
    string fen_boardPosition;
    string fen_activeColor;
    string fen_castlingAvailability;
    string fen_enPassantTarget;
    void parseFEN(const string& fen);
    void extractPieces(const string& fen);

    void verify_castling_K(vector<Move>& moves);
    void verify_castling_Q(vector<Move>& moves);
    void verify_castling_k(vector<Move>& moves);
    void verify_castling_q(vector<Move>& moves);
    void verify_enpassant(vector<Move>& moves);

};
void to_upper(std::string &s);

#endif //ENGINE_BOARD_H
