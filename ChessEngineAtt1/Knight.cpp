#include "Knight.h"

bool Knight::isDestinationValid(int& source, int& destination) {
	
	int direction = destination - source;
	for (const auto& move : validMoves) {
		if (direction == move) { return true; }
	}
	
	return false;
}