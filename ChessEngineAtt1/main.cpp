// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "Chessboard.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Chess Engine Attempt 1\n";
    Chessboard chessboard;
    chessboard.displayBoard();

    chessboard.movePiece("e2", "e3");
    chessboard.displayBoard();

    chessboard.movePiece("a7", "a5");
    chessboard.displayBoard();

    chessboard.movePiece("d1", "h5");
    chessboard.displayBoard();

    chessboard.movePiece("a8", "a6");
    chessboard.displayBoard();

    chessboard.movePiece("h5", "a5");
    chessboard.displayBoard();

    chessboard.movePiece("h7", "h5");
    chessboard.displayBoard();

    chessboard.movePiece("h2", "h4");
    chessboard.displayBoard();

    chessboard.movePiece("a6", "h6");
    chessboard.displayBoard();

    chessboard.movePiece("a5", "c7");
    chessboard.displayBoard();

    chessboard.movePiece("f7", "f6");
    chessboard.displayBoard();

    chessboard.movePiece("c7", "d7");
    chessboard.displayBoard();

    chessboard.movePiece("e8", "f7");
    chessboard.displayBoard();

    chessboard.movePiece("d7", "b7");
    chessboard.displayBoard();

    chessboard.movePiece("d8", "d3");
    chessboard.displayBoard();

    chessboard.movePiece("b7", "b8");
    chessboard.displayBoard();

    chessboard.movePiece("d3", "h7");
    chessboard.displayBoard();

    chessboard.movePiece("b8", "c8");
    chessboard.displayBoard();

    chessboard.movePiece("f7", "g6");
    chessboard.displayBoard();

    chessboard.movePiece("c8", "e6");
    chessboard.displayBoard();

    /*chessboard.movePiece("e2", "e4");
    chessboard.movePiece("e7", "e5");
    chessboard.movePiece("e4", "e5");
    chessboard.movePiece("d7", "d6");
    chessboard.movePiece("d2", "d4");
    chessboard.movePiece("e8", "e7");
    chessboard.movePiece("d4", "d5");
    chessboard.movePiece("e7", "e8");
    chessboard.movePiece("d5", "d6");*/

    chessboard.displayBoard();

    std::string piece = "";
    std::string dest = "";

    /*while (piece != "0" || dest != "0") {
        std::cout << "Piece to move: ";
        std::cin >> piece;
        std::cout << "Destination: ";
        std::cin >> dest;

        chessboard.movePiece(piece, dest);
        chessboard.displayBoard();
    }*/
}
