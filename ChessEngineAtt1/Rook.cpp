#include "Rook.h"

bool Rook::isDestinationValid(int& source, int&destination) {
	int direction = destination - source;
	int cardinalDirection = 0;

	// Already checked if out of bounds (if 1's place is 0 or 1) in Chessboard.cpp so don't need to check that here.

	//Horizontal
	if (direction > -8 && direction < 8 && (source / 10) == (destination / 10)) { 
		this->hasMoved = true;
		return true; 
	}

	else {
		for (const auto& move : validMoves) {
			if (direction / move > 0 && direction % move == 0) { cardinalDirection = move; }
		}

		// Vertical 
		if (cardinalDirection == 10 || cardinalDirection == -10) { 
			this->hasMoved = true;
			return true; 
		}
	}

	return false;
}

bool Rook::getHasMoved() { return this->hasMoved; }