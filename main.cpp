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
using namespace std;




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

void perft(int depth){
    //start time measurement
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();


    Node* root;
    root = new Node(nullptr, new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    root->expand(depth);
    auto perft_x = root->count_leaf_nodes();


    //end time measurement
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    //print result
    cout<<"perft("<<depth<<") = "<<perft_x<<" Duration: "<<duration<<endl;

    delete root;
}




int main(int argc, const char * argv[]) {

    auto out = parseSimpleJson("/Users/petr/CLionProjects/engine/test.json");

    for (auto const& [fen, moves] : out){
        if (moves.size() == 0) {
            continue;
        }
        //if (fen != "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8")
        //    continue;
        test_fen(fen, moves);
    }
    perft(1);
    perft(2);
    perft(3);
    perft(4);


    auto stop = 1;
    
}
