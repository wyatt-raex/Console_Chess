#include "Bishop.h"

bool Bishop::isDestinationValid(int& source, int& destination) {
	int direction = destination - source;
	int cardinalDirection = 0;

	// Already checked if out of bounds (if 1's place is 0 or 1) in Chessboard.cpp so don't need to check that here.
	for (const auto& move : validMoves) {
		if (direction / move > 0 && direction % move == 0) { cardinalDirection = move; }
	}

	if (cardinalDirection == 0) { return false; }

	// Diagonals

	int borderInPath = source; 
	while (borderInPath % 10 != 0) { borderInPath += cardinalDirection; }
	/* borderInPath is the out of bounds location, located in the
		path of which the bishop is moving. It is used to prevent moves such as 25 -> 79 (d1 -> h6) being valid to the program. */

	if (cardinalDirection == -9 || cardinalDirection == -11) {
		if (destination > borderInPath) { return true; }
	}
	else if (cardinalDirection == 9 || cardinalDirection == 11) {
		if (destination < borderInPath) { return true; }
	}

	return false;
}