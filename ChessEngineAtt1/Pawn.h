#pragma once
#include "pch.h"
#include "Piece.h"

#include <iostream>
#include <string>

class Pawn : public Piece
{
private:

public:
	using Piece::Piece; // Tells C++ that we are using Piece's constructor
	bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) override;

	bool isDestinationValid(int& source, int& destination) override { return false; };
};

