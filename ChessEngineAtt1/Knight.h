#pragma once
#include "Piece.h"

#include <iostream>
#include <string>
#include <array>

class Knight : public Piece
{
private:
	std::array<int, 8> validMoves = {8, 12, 19, 21, -8, -12, -19, -21};
public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

