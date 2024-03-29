//
// Created by Petr on 23.03.2024.
//

#include "node.h"

Node::Node(Node *parent, Board *board) {
    this->parent = parent;
    this->board = board;
    this->move = nullptr;
}

Node::Node(Node *parent, Board *board,Move *move) {
    this->parent = parent;
    this->board = board;
    this->move = move;
}

Node* Node::expand(int depth,ofstream& file) {
    if (depth == 0){
        string uci_path="";
        auto tmp = this;
        while (tmp->parent != nullptr){
            uci_path = tmp->move->get_uci() + "," + uci_path;
            tmp = tmp->parent;
        }

        //append to file fen position
        file << this->board->get_fen() <<" ; "<< uci_path << endl;
        return this;
    }
    vector<Move> moves = this->board->get_legal_moves();
    for (auto& m: moves){
        Board new_board = this->board->deep_copy();
        new_board.push_move(m);
        Node* new_node = new Node(this, &new_board,&m);
        this->children.push_back(new_node);
        new_node->expand(depth-1, file);
    }
    return this;
}

uint64_t Node::count_leaf_nodes() {
    if (this->children.empty()){
        return 1;
    }
    uint64_t sum = 0;
    for (auto& c: this->children){
        sum += c->count_leaf_nodes();
    }
    return sum;
}