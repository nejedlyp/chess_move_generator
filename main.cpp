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

using namespace std;



class Board{
public:
    string fen;
    string fen_boardPosition;
    string fen_activeColor;
    string fen_castlingAvailability;
    string fen_enPassantTarget;

    bool active_color;
    bool castling_K;
    bool castling_k;
    bool castling_Q;
    bool castling_q;
    string enPassant_square;
    int halfMoveClock;
    int fullMoveNumber;
    
    Bitboards bitboards;
    
    Board(const string& fen);
    
    vector<Piece*> pieces;
    vector<Piece*> pieces_white;
    vector<Piece*> pieces_black;
    
    King* wk = nullptr;
    King* bk = nullptr;
    
    vector<Move> get_legal_moves();
    vector<string> get_legal_moves_uci();

    
    void parseFEN(const string& fen);
    void extractPieces(const string& fen);

};

vector<Move> Board::get_legal_moves(){
    vector<Move> moves = vector<Move>();
    
    King* king = (this->fen_activeColor == "w") ? wk : bk;
    std::vector<Piece*>* friends = (this->fen_activeColor == "w") ? &pieces_white : &pieces_black;
    std::vector<Piece*>* opponents = (this->fen_activeColor == "w") ? &pieces_black : &pieces_white;

    
    auto checking_pieces = king->get_checking_pieces(*opponents, &this->bitboards);
    
    // double check
    if (checking_pieces.size() == 2)
    {
        king->get_uci(&this->bitboards, moves);
    }
    // single check
    else if (checking_pieces.size() == 1){
        vector<Move> pseudolegal_moves = vector<Move>();
        auto possible_squares_bb = getBitboardRay(checking_pieces[0]->index, king->index) & ~king->bitboard;
        auto possible_squares_idxs = bitboard2index(possible_squares_bb);
        for (const auto& p: *friends){
            p->get_uci(&this->bitboards, pseudolegal_moves);
        }
        
        for (auto &m: pseudolegal_moves){
            if (m.from == king->index){
                moves.push_back(m);
                continue;
            }
            
            // check if m.to in possible_squares_idx
            auto it = std::find(possible_squares_idxs.begin(), possible_squares_idxs.end(), m.to);
            

            if (it != possible_squares_idxs.end()) {
                moves.push_back(m);
            }
        }
        auto s=1;
    }
    // no check
    else{
        for (const auto& p: *friends){
            p->get_uci(&this->bitboards, moves);
        }
    }
    
    return moves;
}



vector<string> Board::get_legal_moves_uci(){
    vector<string> moves = vector<string>();
    for (const auto& p: this->get_legal_moves()){
        moves.push_back(p.uci());
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
    this->parseFEN(fen);
    this->extractPieces(this->fen_boardPosition);
    this->bitboards = Bitboards(this->pieces);
    int s= 1;
    
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
static const std::map<std::pair<int, int>, uint64_t> BITBOARD_RAY_MAP = generateRayMap();




int main(int argc, const char * argv[]) {
    print_bitboard(BITBOARD_RAY_MAP.at(std::make_pair(SquareToIndex.at("A8"), SquareToIndex.at("B1"))));
    
    test_fen("3Bk3/8/8/8/1Q5q/5N2/6P1/4K2R w - - 0 1",vector<string>({"B4H4","D8H4","E1D1","E1D2","E1E2","E1F1","F3H4","G2G3","H1H4"}));
    test_fen("r1bqk2r/ppp1ppbp/2n2np1/3p4/3P4/2NBPN2/PPPB1PPP/R2QK2R w - - 0 1",vector<string>({"A1B1","A1C1","A2A3","A2A4","B2B3","B2B4","C3A4","C3B1","C3B5","C3D5","C3E2","C3E4","D1B1","D1C1","D1E2","D2C1","D3A6","D3B5","D3C4","D3E2","D3E4","D3F1","D3F5","D3G6","E1E2","E1F1","E3E4","F3E5","F3G1","F3G5","F3H4","G2G3","G2G4","H1F1","H1G1","H2H3","H2H4"}));

    test_fen("4k3/4r3/8/8/7b/8/8/4K3 w - - 0 1",vector<string>({"E1F1","E1D1","E1D2"}));
    
    auto start = std::chrono::high_resolution_clock::now();
    auto fen_start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    auto fen = "r1bqk2r/ppp1ppbp/2n2np1/3p4/3P4/2NBPN2/PPPB1PPP/R2QK2R w - - 0 1";
    
    auto b = Board(fen);
    auto moves = b.get_legal_moves();
    for (auto &m: moves){
        cout<<m<<endl;
    }

    // Get the ending point
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
    
}
