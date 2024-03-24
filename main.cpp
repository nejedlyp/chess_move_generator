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
#include "board.h"
#include "node.h"
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ostream>
using namespace std;


void test_move_post_fen_lg(string fen, string uci, string post_fen){
    cout<<"----------------------------------------"<<endl;
    cout<<"Test: "<<fen<<endl;
    auto board = Board(fen);
    auto moves = board.get_legal_moves();
    bool success = false;
    for (auto& m: moves){
        if (m.get_uci() == uci){
            success = true;
            board.push_move(m);
            break;
        }
    }
    if (!success){
        cout<<"Invalid move"<<endl;
        return;
    }
    auto fen2 = board.get_fen();
    cout<<"Out:  "<<fen2<<endl;
    if (post_fen != fen2){
        cout<<"Invalid"<<endl;
        cout<<"Expected: "<<post_fen<<endl;
        cout<<"Got:      "<<fen2<<endl;
    }
    else{
        cout<<"OK"<<endl;
    }

}

void test_get_fen(string fen){
    cout<<"----------------------------------------"<<endl;
    cout<<"Test: "<<fen<<endl;
    auto board = Board(fen);
    auto fen2 = board.get_fen();
    cout<<"Out:  "<<fen2<<endl;
    if (fen != fen2){
        cout<<"Invalid"<<endl;
    }
    else{
        cout<<"OK"<<endl;
    }

}


void test_fen(string fen, vector<string> correct){
    cout<<"----------------------------------------"<<endl;
    cout<<"Test: "<<fen<<endl;
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

    bool success = true;

    if (correct.size() != moves.size()) {
        cout << "Different number of moves." << endl;
        return;
    }
    for (int i=0; i < correct.size(); i++){
        if (correct[i] == moves[i]){
            //cout<< "OK: " << moves[i] << endl;
        }
        else{
            cout<< "Invalid: "<< correct[i]<<"!="<<moves[i] << endl;
            success = false;
        }
    }
}

void perft(int depth,const string& fen_positions){
    ofstream file("fen_positions.txt", ios::trunc);


    //start time measurement
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();


    Node* root;
    root = new Node(nullptr, new Board(fen_positions));
    root->expand(depth,file);
    auto perft_x = root->count_leaf_nodes();
    file.close();

    //end time measurement
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    //print result
    cout<<"perft("<<depth<<") = "<<perft_x<<" Duration: "<<duration<<endl;

    delete root;
}




int main(int argc, const char * argv[]) {
    test_move_post_fen_lg("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                          "E2E4",
                      "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");



    auto out = parseSimpleJson("/Users/petr/CLionProjects/engine/test.json");

    for (auto const& [fen, moves] : out){
        if (moves.size() == 0) {
            continue;
        }
        //if (fen != "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8")
        //    continue;
        test_fen(fen, moves);
        test_get_fen(fen);
    }
    const string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    const string fen_start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    //perft(1,fen_start);
    //perft(2,fen_start);
    //perft(3,fen_start);
    //perft(4,fen_start);
    perft(5,fen_start);


    auto stop = 1;
    
}
