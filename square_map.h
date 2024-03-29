//
//  SquareMap.h
//  Engine
//
//  Created by Petr on 10.03.2024.
//

#ifndef SquareMap_h
#define SquareMap_h

#include <unordered_map>
#include <string>

static const std::unordered_map<std::string, int> SquareToIndex = {
    {"A8",63},
    {"B8",62},
    {"C8",61},
    {"D8",60},
    {"E8",59},
    {"F8",58},
    {"G8",57},
    {"H8",56},
    
    {"A7",55},
    {"B7",54},
    {"C7",53},
    {"D7",52},
    {"E7",51},
    {"F7",50},
    {"G7",49},
    {"H7",48},
    
    {"A6",47},
    {"B6",46},
    {"C6",45},
    {"D6",44},
    {"E6",43},
    {"F6",42},
    {"G6",41},
    {"H6",40},
    
    {"A5",39},
    {"B5",38},
    {"C5",37},
    {"D5",36},
    {"E5",35},
    {"F5",34},
    {"G5",33},
    {"H5",32},
    
    {"A4",31},
    {"B4",30},
    {"C4",29},
    {"D4",28},
    {"E4",27},
    {"F4",26},
    {"G4",25},
    {"H4",24},
    
    {"A3",23},
    {"B3",22},
    {"C3",21},
    {"D3",20},
    {"E3",19},
    {"F3",18},
    {"G3",17},
    {"H3",16},
    
    {"A2",15},
    {"B2",14},
    {"C2",13},
    {"D2",12},
    {"E2",11},
    {"F2",10},
    {"G2",9},
    {"H2",8},
    
    {"A1",7},
    {"B1",6},
    {"C1",5},
    {"D1",4},
    {"E1",3},
    {"F1",2},
    {"G1",1},
    {"H1",0},
};

static const std::unordered_map<int, std::string> IndexToSquare = {
    {63,"A8"},
    {62,"B8"},
    {61,"C8"},
    {60,"D8"},
    {59,"E8"},
    {58,"F8"},
    {57,"G8"},
    {56,"H8"},
    
    {55,"A7"},
    {54,"B7"},
    {53,"C7"},
    {52,"D7"},
    {51,"E7"},
    {50,"F7"},
    {49,"G7"},
    {48,"H7"},
    
    {47,"A6"},
    {46,"B6"},
    {45,"C6"},
    {44,"D6"},
    {43,"E6"},
    {42,"F6"},
    {41,"G6"},
    {40,"H6"},
    
    {39,"A5"},
    {38,"B5"},
    {37,"C5"},
    {36,"D5"},
    {35,"E5"},
    {34,"F5"},
    {33,"G5"},
    {32,"H5"},
    
    {31,"A4"},
    {30,"B4"},
    {29,"C4"},
    {28,"D4"},
    {27,"E4"},
    {26,"F4"},
    {25,"G4"},
    {24,"H4"},
    
    {23,"A3"},
    {22,"B3"},
    {21,"C3"},
    {20,"D3"},
    {19,"E3"},
    {18,"F3"},
    {17,"G3"},
    {16,"H3"},
    
    {15,"A2"},
    {14,"B2"},
    {13,"C2"},
    {12,"D2"},
    {11,"E2"},
    {10,"F2"},
    {9,"G2"},
    {8,"H2"},
    
    {7,"A1"},
    {6,"B1"},
    {5,"C1"},
    {4,"D1"},
    {3,"E1"},
    {2,"F1"},
    {1,"G1"},
    {0,"H1"},
};

#endif /* SquareMap_h */
