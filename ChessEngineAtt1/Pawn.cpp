#include "Pawn.h"

bool Pawn::isDestinationValid (int& source, int& destination, bool& isPieceAtDest) {
	int direction = destination - source;

	switch (this->getTeam()) {
		case 'w':
			if ((direction == 9 || direction == 11) && isPieceAtDest) { return true; } // Pawn attacking diagonally requires a piece to attack
			else if (direction == 10 && !isPieceAtDest) { return true; } // Forward Movement
			else if (direction == 20 && source / 10 == 3 && !isPieceAtDest) { return true; } // 2 Spaces first pawn move only
			break;

		case 'b':
			if ((direction == -9 || direction == -11) && isPieceAtDest) { return true; } // Pawn attacking diagonally requires a piece to attack
			else if (direction == -10 && !isPieceAtDest) { return true; } // Forward Movement
			else if (direction == -20 && source / 10 == 8 && !isPieceAtDest) { return true; } // 2 Spaces first pawn move only
			break;
	}

	return false;
}
