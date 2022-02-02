#pragma once
#include "Piece.h"

#include <iostream>
#include <string>
#include <array>

class Rook : public Piece
{
private:
	std::array<int, 2> validMoves = { 10, -10 };
	bool hasMoved = false;
public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;
	bool getHasMoved();

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

