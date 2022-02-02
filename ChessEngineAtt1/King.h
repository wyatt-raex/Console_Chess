#pragma once
#include "Piece.h"

#include <iostream>
#include <string>
#include <array>

class King : public Piece
{
private:
	std::array<int, 8> validMoves = { -11, -10, -9, -1, 1, 9, 10, 11 };
	bool hasMoved = false;
public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;
	bool getHasMoved();

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

