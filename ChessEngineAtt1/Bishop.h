#pragma once
#include "Piece.h"

#include <iostream>
#include <string>
#include <array>

class Bishop : public Piece
{
private:
	std::array<int, 4> validMoves = { -11 , -9, 9, 11 };
public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

