#pragma once

#include "pch.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Empty.h"

#include <iostream>
#include <string>
#include <array>

class Chessboard {
private:
	Piece* board[120];
	Piece* empty = new Empty('_', "__", "empty", '0');

	Piece* wPawn = new Pawn('p', "wP", "white_pawn", 'w');
	Piece* bPawn = new Pawn('p', "bP", "black_pawn", 'b');
	Piece* wRook = new Rook('r', "wR", "white_rook", 'w');
	Piece* bRook = new Rook('r', "bR", "black_rook", 'b');
	Piece* wKnight = new Knight('n', "wN", "white_knight", 'w');
	Piece* bKnight = new Knight('n', "bN", "black_knight", 'b');
	Piece* wBishop = new Bishop('b', "wB", "white_bishop", 'w');
	Piece* bBishop = new Bishop('b', "bB", "black_bishop", 'b');
	Piece* wQueen = new Queen('q', "wQ", "white_queen", 'w');
	Piece* bQueen = new Queen('q', "bQ", "black_queen", 'b');
	Piece* wKing = new King('k', "wK", "white_king", 'w');
	Piece* bKing = new King('k', "bK", "black_king", 'b');

	bool whiteTurn = true;

	bool canEnPassant = false;
	int enPassantPos = 0;
	int enPassantPawnPos = 0;

	bool wKingMoved = false;
	bool bKingMoved = false;
	bool wRook1Moved = false;
	bool wRook2Moved = false;
	bool bRook1Moved = false;
	bool bRook2Moved = false;

	bool stalemate = false;
	bool checkmate = false;

	const int m_boardStart = 22;
	const int m_boardEnd = 99;

	const std::array<int, 7> kCheck_l = { -1, -2, -3, -4, -5, -6, -7 };
	const std::array<int, 7> kCheck_r = { 1, 2, 3, 4, 5, 6, 7 };
	const std::array<int, 7> kCheck_d = { -10, -20, -30, -40, -50, -60, -70 };
	const std::array<int, 7> kCheck_u = { 10, 20, 30, 40, 50, 60, 70 };
	const std::array<int, 7> kCheck_dl = { -11, -22, -33, -44, -55, -66, -77 };
	const std::array<int, 7> kCheck_dr = { 9, 18, 27, 36, 45, 54, 63 };
	const std::array<int, 7> kCheck_ul = { -9, -18, -27, -36, -45, -54, -63 };
	const std::array<int, 7> kCheck_ur = { 11, 22, 33, 44, 55, 66, 77 };

	const std::array<std::array<int, 7>, 8> kCheck = { kCheck_l, kCheck_r, kCheck_d, kCheck_u, kCheck_dl, kCheck_dr, kCheck_ul, kCheck_ur };

	const std::array<int, 8> possKingMoves = { -11, -10, -9, -1, 1, 9, 10, 11 };
	const std::array<int, 56> possQueenMoves = { -77, -70, -66, -63, -60, -55, -54, -50, -45, -44, -40, -36, -33, -30, -27, -22, -20 -18, -11, -10, -9, -7, -6, -5, -4, -3, -2, -1, 
												1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 18, 20, 22, 27, 30, 33, 36, 40, 44, 45, 50, 54, 55, 60, 63, 66, 70, 77};
	const std::array<int, 28> possBishopMoves = { -77, -66, -63, -55, -54, -45, -44, -36, -33, -27, -22, -18, -11, -9, 9, 11, 18, 22, 27, 33, 36, 44, 45, 54, 55, 63, 66, 77 };
	const std::array<int, 8> possKnightMoves = { 8, 12, 19, 21, -8, -12, -19, -21 };
	const std::array<int, 28> possRookMoves = { -70, -60, -50, -40, -30, -20, -10, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 10, 20, 30, 40, 50, 60, 70 };
	const std::array<int, 8> possPawnMoves = { -20, -11, -10, -9, 9, 10, 11, 20 };

	bool isMoveValid(int pos1, int pos2);
	bool canCastle(int& pos_king, int& pos_rook);
	void checkEnPassant(int& pos1, int& pos2);
	bool isPathBlocked(int& pos1, int& pos2);
	bool isInCheck(Piece* king);
	bool isInStalemate(Piece* king);
	bool isInCheckmate(Piece* king);

	// ********** MISC METHODS ********** //
	int static coordToIndex(std::string coordinate);
	int findPiece(Piece* piece);
	bool isPosOutOfBounds(int& pos);
	bool hasAvailableMove(char& teamToCheck);

public:
	Chessboard();
	void displayBoard();
	void movePiece(std::string source, std::string destination);
};


