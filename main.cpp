//
//  main.cpp
//  Engine
//
//  Created by Petr on 09.03.2024.
//
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
#include "json.hpp"
using namespace std;

void to_upper(std::string &s) {
    for (char &c : s) {
        c = std::toupper(static_cast<unsigned char>(c)); // Use static_cast to ensure the correct overload
    }
}


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

void Board::verify_enpassant(vector<Move> &moves) {
    // TODO: verify that king is not in check after the enpassant move
    if (this->fen_enPassantTarget == "-") {
        return;
    }
    to_upper(this->fen_enPassantTarget);
    int square = SquareToIndex.at(this->fen_enPassantTarget);

    if (this->fen_activeColor == "w") {
        uint64_t possible_squares = generatePseudolegalBlackPawnCapturesFromSquare(square);
        auto tmp = bitboard2index(possible_squares);
        for (auto& k: tmp){
            if (square_piece_map[k] != nullptr && square_piece_map[k]->type == 'P'){
                moves.push_back(Move(k, square));
            }
        }

    } else {
        uint64_t possible_squares = generatePseudolegalWhitePawnCapturesFromSquare(square);
        auto tmp = bitboard2index(possible_squares);
        for (auto& k: tmp){
            if (square_piece_map[k] != nullptr && square_piece_map[k]->type == 'p'){
                moves.push_back(Move(k, square));
            }
        }
    }
}

void Board::verify_castling_K(vector<Move> &moves) {
    if (!this->castling_K){
        return;
    }
    if (this->fen_activeColor != "w") {
        return;
    }
    if (square_piece_map[SquareToIndex.at("F1")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("G1")] != nullptr) {
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("E1"))){
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("F1"))){
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("G1"))){
        return;
    }
    moves.push_back(Move("E1G1"));
}

void Board::verify_castling_Q(vector<Move> &moves) {
    if (!this->castling_Q){
        return;
    }
    if (this->fen_activeColor != "w") {
        return;
    }
    if (square_piece_map[SquareToIndex.at("D1")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("C1")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("B1")] != nullptr) {
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("E1"))){
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("D1"))){
        return;
    }
    if (this->bitboards.attack_black_no_wk & (1ULL << SquareToIndex.at("C1"))){
        return;
    }
    moves.push_back(Move("E1C1"));
}


void Board::verify_castling_k(vector<Move> &moves) {
    if (!this->castling_k){
        return;
    }
    if (this->fen_activeColor != "b") {
        return;
    }
    if (square_piece_map[SquareToIndex.at("F8")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("G8")] != nullptr) {
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("E8"))){
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("F8"))){
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("G8"))){
        return;
    }
    moves.push_back(Move("E8G8"));
}

void Board::verify_castling_q(vector<Move> &moves) {
    if (!this->castling_q) {
        return;
    }
    if (this->fen_activeColor != "b") {
        return;
    }
    if (square_piece_map[SquareToIndex.at("D8")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("C8")] != nullptr) {
        return;
    }
    if (square_piece_map[SquareToIndex.at("B8")] != nullptr) {
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("E8"))) {
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("D8"))) {
        return;
    }
    if (this->bitboards.attack_white_no_bk & (1ULL << SquareToIndex.at("C8"))) {
        return;
    }
    moves.push_back(Move("E8C8"));
}

Board Board::deep_copy() const{
    string fen = this->get_fen();
    return Board(fen);
}

void Board::push_move(Move m){
    Piece* p = square_piece_map[m.from];
    square_piece_map[m.to] = p;
    square_piece_map[m.from] = nullptr;
    p->index = m.to;
}


// loop over square_piece_map and output fen string
string Board::get_fen() const{
    string fen = "";
    int empty = 0;
    for (int i = 63; i >= 0; --i) {

        if (square_piece_map.at(i) == nullptr) {
            empty++;
        } else {
            fen += (empty == 0) ? "" : to_string(empty);
            fen += square_piece_map.at(i)->type;
            empty = 0;
        }
        if (i % 8 == 0 && i != 0) {
            fen += (empty == 0) ? "" : to_string(empty);
            fen += "/";
            empty = 0;
        }

    }
    fen += " ";
    fen += this->fen_activeColor;
    fen += " ";
    fen += this->fen_castlingAvailability;
    fen += " ";
    fen += this->fen_enPassantTarget;
    fen += " ";
    fen += to_string(this->halfMoveClock);
    fen += " ";
    fen += to_string(this->fullMoveNumber);
    return fen;
}

void Board::show() const{
    cout<<"FEN: "<<this->get_fen()<<endl;
    cout<< "+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;
    for (int i = 63; i >= 0; --i) {

        if (square_piece_map.at(i) == nullptr) {
            cout << "|     ";
        } else {
            cout << "|  "<<square_piece_map.at(i)->type<<"  ";
        }
        if (i % 8 == 0) {
            cout <<"|  "<< (i/8)+1  <<endl;
            cout<< "+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;
        }
    }
    cout<<"   A     B     C     D     E     F     G     H"<<endl;
    cout << endl;

}


vector<Move> Board::get_legal_moves(){
    vector<Move> moves = vector<Move>();
    
    King* king = (this->fen_activeColor == "w") ? wk : bk;
    std::vector<Piece*>* friends = (this->fen_activeColor == "w") ? &pieces_white : &pieces_black;
    std::vector<Piece*>* opponents = (this->fen_activeColor == "w") ? &pieces_black : &pieces_white;

    // finds check and sets check_attack_filter in Piece class
    king->find_checks(*friends, *opponents, &this->bitboards);

    // finds pins and sets pin_attack_filter in Piece class
    king->find_pins(*friends, *opponents, &this->bitboards);

    for (const auto& p: *friends){
        p->get_uci(&this->bitboards, moves);
    }

    verify_castling_K(moves);
    verify_castling_Q(moves);
    verify_castling_k(moves);
    verify_castling_q(moves);

    verify_enpassant(moves);


    return moves;
}



vector<string> Board::get_legal_moves_uci(){
    vector<string> moves = vector<string>();
    for (const auto& p: this->get_legal_moves()){
        moves.push_back(p.get_uci());
    }
    return moves;
}


void Board::parseFEN(const string& fen){
    // Extract the six fields from the FEN string
    this->fen = fen;

    istringstream fenStream(fen);
    fenStream >> this->fen_boardPosition;
    fenStream >> this->fen_activeColor;
    fenStream >> this->fen_castlingAvailability;
    fenStream >> this->fen_enPassantTarget;
    fenStream >> this->halfMoveClock;
    fenStream >> this->fullMoveNumber;

    this->active_color = this->fen_activeColor == "w";
    this->castling_K = this->fen_castlingAvailability.find("K") != string::npos;
    this->castling_k = this->fen_castlingAvailability.find("k") != string::npos;
    this->castling_Q = this->fen_castlingAvailability.find("Q") != string::npos;
    this->castling_q = this->fen_castlingAvailability.find("q") != string::npos;
    this->enPassant_square = this->fen_enPassantTarget;
}


void Board::extractPieces(const string& fen){
    int index = 0;
    for (int i = 0; i < fen.length(); ++i) {
        if (fen[i] == ' ') {
            break;
        }
        if (fen[i] == '/') {
            continue;
        }
        
        char c = fen[i];
        if (isdigit(c)) {
            index += c - '0';
        } else {
            int boardPosition = 63 - index;
            switch (c) {
                case 'p': pieces.push_back(new Pawn(false, boardPosition)); break;
                case 'r': pieces.push_back(new Rook(false, boardPosition)); break;
                case 'n': pieces.push_back(new Knight(false, boardPosition)); break;
                case 'b': pieces.push_back(new Bishop(false, boardPosition)); break;
                case 'q': pieces.push_back(new Queen(false, boardPosition)); break;
                case 'k': pieces.push_back(new King(false, boardPosition)); break;
                case 'P': pieces.push_back(new Pawn(true, boardPosition)); break;
                case 'R': pieces.push_back(new Rook(true, boardPosition)); break;
                case 'N': pieces.push_back(new Knight(true, boardPosition)); break;
                case 'B': pieces.push_back(new Bishop(true, boardPosition)); break;
                case 'Q': pieces.push_back(new Queen(true, boardPosition)); break;
                case 'K': pieces.push_back(new King(true, boardPosition)); break;
                    
            }
            index++;
        }
    }
    
    
    for (const auto& p: pieces){
        square_piece_map[p->index] = p;
        if (p->color){
            pieces_white.push_back(p);
        }
        else{
            pieces_black.push_back(p);
        }
        
        if (p->type == 'K'){
            wk = (King*) p;
        }
        if (p->type == 'k'){
            bk = (King*) p;
        }
    }
    
}

Board::Board(const string& fen){
    for (int i = 0; i < 64; ++i) {
        square_piece_map[i] = nullptr;
    }


    this->parseFEN(fen);
    this->extractPieces(this->fen_boardPosition);
    this->bitboards = Bitboards(this->pieces);

};


void test_fen(string fen, vector<string> correct){
    sort(correct.begin(), correct.end());
    
    auto moves = Board(fen).get_legal_moves_uci();
    sort(moves.begin(), moves.end());
    
    for (auto& m: correct){
        cout<<m<<",";
    }
    cout<<endl;
    for (auto& m: moves){
        cout<<m<<",";
    }
    cout<<endl;
    
    
    if (correct.size() != moves.size()) {
        cout << "Different number of moves." << endl;
        return;
    }
    
    for (int i=0; i < correct.size(); i++){
        if (correct[i] == moves[i]){
            cout<< "OK: " << moves[i] << endl;
        }
        else{
            cout<< "Invalid: "<< correct[i]<<"!="<<moves[i] << endl;
        }
    }
}






int main(int argc, const char * argv[]) {

    auto out = parseSimpleJson("/Users/petr/CLionProjects/engine/test.json");

    for (auto const& [fen, moves] : out){
        if (moves.size() == 0) {
            continue;
        }
        test_fen(fen, moves);
    }

    
}
