#include "King.h"

bool King::isDestinationValid(int& source, int& destination) {
	int direction = destination - source;

	// Already checked if out of bounds (if 1's place is 0 or 1) in Chessboard.cpp so don't need to check that here.
	for (const auto& move : validMoves) {
		if (direction == move) { 
			this->hasMoved = true;
			return true; 
		}
	}
	return false;
}

bool King::getHasMoved() { return this->hasMoved; }