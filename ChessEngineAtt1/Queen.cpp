#include "Queen.h"

bool Queen::isDestinationValid(int& source, int& destination) {
	int direction = destination - source;
	int cardinalDirection = 0;

	// Already checked if out of bounds (if 1's place is 0 or 1) in Chessboard.cpp so don't need to check that here.

	//Horizontal
	if (direction > -8 && direction < 8 && (source / 10) == (destination / 10)) { return true; } 


	else {
		for (const auto& move : validMoves) {
			if (direction / move > 0 && direction % move == 0) { cardinalDirection = move; }
		}

		if (cardinalDirection == 0) { return false; }

		// Vertical 
		if (cardinalDirection == 10 || cardinalDirection == -10) { return true; }

		// Diagonals

		int borderInPath = source;
		while (borderInPath % 10 != 0) { borderInPath += cardinalDirection; }
		/* borderInPath is the out of bounds location, located in the
		path of which the queen is moving. It is used to prevent moves such as 25 -> 79 (d1 -> h6) being valid to the program. */

		if (cardinalDirection == -9 || cardinalDirection == -11) {
			if (destination > borderInPath) { return true; }
		}
		else if (cardinalDirection == 9 || cardinalDirection == 11) {
			if (destination < borderInPath) { return true; }
		}

		
	}

	return false;
}