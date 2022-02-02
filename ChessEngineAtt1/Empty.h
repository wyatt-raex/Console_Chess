#pragma once
#include "Piece.h"

#include <iostream>
#include <string>

class Empty : public Piece
{
private:

public:
	using Piece::Piece;
	bool isDestinationValid(int& source, int& destination) override;

	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override { return false; };
};

