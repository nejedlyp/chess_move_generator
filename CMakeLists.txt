cmake_minimum_required(VERSION 3.27)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(engine main.cpp
        move.cpp
        move.hpp
        piece.cpp
        piece.hpp
        bishop.hpp
        bishop.cpp
        bitboards.cpp
        bitboards.hpp
        king.cpp
        king.hpp
        knight.cpp
        knight.hpp
        queen.cpp
        queen.hpp
        rook.cpp
        rook.hpp
        square_map.h
        pawn.cpp
        pawn.hpp
        json.hpp
        node.cpp
        node.h
        board.cpp
        board.h
)
