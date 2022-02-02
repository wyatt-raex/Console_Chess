#pragma once
#include "Piece.h"

#include <iostream>
#include <string>
#include <array>

class Queen : public Piece
{
private:
	std::array<int, 6> validMoves = { 11, 10, 9, -9, -10, -11 };
public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

