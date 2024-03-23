//
// Created by Petr on 23.03.2024.
//

#ifndef ENGINE_NODE_H
#define ENGINE_NODE_H

#include <stdio.h>
#include <vector>
#include "board.h"


using namespace std;

class Node {
public:
    Node* parent;
    vector<Node*> children;
    Board* board;
    Move* move;

    Node(Node* parent, Board* board,Move*move);
    Node(Node* parent, Board* board);

    Node* expand(int depth);
    uint64_t count_leaf_nodes();
};


#endif //ENGINE_NODE_H
