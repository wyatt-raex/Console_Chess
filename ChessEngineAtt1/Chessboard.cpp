#include "Chessboard.h"

Chessboard::Chessboard() {
	for (int i = 0; i < 120; i++) {
		//Set pawns
		if (i / 10 == 3 && i % 10 != 1 && i % 10 != 0) {
			board[i] = wPawn;
		}
		else if (i / 10 == 8 && i % 10 != 1 && i % 10 != 0) {
			board[i] = bPawn;
		}
		else { board[i] = empty; }
	}

	board[22] = wRook;
	board[23] = wKnight;
	board[24] = wBishop;
	board[25] = wQueen;
	board[26] = wKing;
	board[27] = wBishop;
	board[28] = wKnight;
	board[29] = wRook;

	board[92] = bRook;
	board[93] = bKnight;
	board[94] = bBishop;
	board[95] = bQueen;
	board[96] = bKing;
	board[97] = bBishop;
	board[98] = bKnight;
	board[99] = bRook;

	this->whiteTurn = true;
}

void Chessboard::displayBoard() {
	std::cout << "\n\n\n";

	std::string display = "";
	std::string temp = "1   ";

	//Need to display the board between indexes 22-99 excluding indexes with 0's and 1's int the 1's place (e.g. 40, 81)
	for (int i = m_boardStart; i <= m_boardEnd + 1; ++i) {

		if (i % 10 != 0 && i % 10 != 1) { 
			temp += this->board[i]->getId() + " ";
		}
		else if (i % 10 == 0) {
			temp = temp + "\n\n";
			display = temp + display;
			temp = std::to_string((i / 10) - 1) + "   ";
		}
	}

	display = display + "    A  B  C  D  E  F  G  H";

	std::cout << display << "\n";
}

void Chessboard::movePiece(std::string source, std::string destination) {
	int pos1 = coordToIndex(source);
	int pos2 = coordToIndex(destination);

	bool isPos1PieceWhite = this->board[pos1]->getTeam() == 'w';
	bool isCorrectTurn = isPos1PieceWhite == this->whiteTurn;

	if (isCorrectTurn) {
		if (isMoveValid(pos1, pos2)) {
			this->board[pos2] = this->board[pos1];
			this->board[pos1] = this->empty;

			// Set if kings or rooks have moved already. At this point the piece has successfully moved.
			if (source == "e8") { 
				if (destination == "a8") { this->bRook1Moved = true; }
				else if (destination == "h8") { this->bRook2Moved = true; }
				this->bKingMoved = true; 
			}
			else if (source == "e1") { 
				if (destination == "a1") { this->wRook1Moved = true; }
				else if (destination == "h1") { this->wRook2Moved = true; }
				this->wKingMoved = true; 
			}
			else if (source == "a8") { this->bRook1Moved = true; }
			else if (source == "h8") { this->bRook2Moved = true; }
			else if (source == "a1") { this->wRook1Moved = true; }
			else if (source == "h1") { this->wRook2Moved = true; }

			//Check for Stalemate & Checkmate
			if (this->whiteTurn) {
				this->stalemate = isInStalemate(bKing);
				if (!this->stalemate) {
					this->checkmate = isInCheckmate(bKing);
				}
			}
			else {
				this->stalemate = isInStalemate(wKing);
				if (!this->stalemate) {
					this->checkmate = isInCheckmate(wKing);
				}
			}

			// sets canEnPassant if in the next move the other player can do enPassant. Has nothing to do with checking if a move is valid
			checkEnPassant(pos1, pos2);

			whiteTurn = !whiteTurn;
		}
	}
}

bool Chessboard::isMoveValid(int pos1, int pos2) {
	/*
	* General Invalid Move Reasons
	* - Source or Destination Out of Bounds
	* - Destination is same team as source (exception being castling)
	* - Pieces movement is illegal
	* - Path between Source & Destination is blocked (exception being knight)
	* - King is in check
	*
	* if (!out of bounds)
	*	if (castling) { doCastleMethod() }
	*	else if (!same team)
	*		if (!invalid rule movment)
	*			if (!path blocked)
	*				if (!kingInCheck)
	*					THEN move;
	*				else { move so king not in check }
	*
	* cout "ERROR: Can't move for x reason"
	*/

	if (pos1 < 0 || pos1 > 119 || pos2 < 0 || pos2 > 119) { return false; }

	Piece* movePiece = this->board[pos1]; // Piece being moved
	Piece* destPiece = this->board[pos2]; // Destination to move to

	bool isPos1OutOfBounds = (pos1 % 10 == 0) || (pos1 % 10 == 1) || pos1 < m_boardStart || pos1 > m_boardEnd;
	bool isPos2OutOfBounds = (pos2 % 10 == 0) || (pos2 % 10 == 1) || pos2 < m_boardStart || pos2 > m_boardEnd;


	bool isSameTeam = movePiece->getTeam() == destPiece->getTeam();
	bool wantsToCastle = isSameTeam && (movePiece->getType() == 'k') && (destPiece->getType() == 'r');
	
	bool isDestinationValid = false; 
	if (movePiece->getType() == 'p') {
		bool isPieceAtDest = destPiece->getType() != empty->getType(); // True if a piece is at destination (if destination isn't empty)
		isDestinationValid = movePiece->isDestinationValid(pos1, pos2, isPieceAtDest);
	}
	else {
		isDestinationValid = movePiece->isDestinationValid(pos1, pos2);
	}

	bool pathBlocked = isPathBlocked(pos1, pos2);

	bool isOwnKingInCheck = false;
	if (movePiece->getTeam() == 'w') { isOwnKingInCheck = isInCheck(this->wKing); }
	else { isOwnKingInCheck = isInCheck(this->bKing); }

	if (isPos1OutOfBounds || isPos2OutOfBounds || pos1 == pos2) {
		return false;
	}
	else {
		// If the piece being moved doesn't correspond to the player's turn move is illegal (white can't move black's pieces
		if (wantsToCastle) { 
			
			// in bool var wantsToCastle, already checked if movePiece is king and destPiece is rook and that they're on same team
			return canCastle(pos1, pos2); 
		}
		else if (!isSameTeam) {
			// En Passant Specifc
			if (canEnPassant) {
				if (movePiece->getType() == 'p' && pos2 == enPassantPos) { // Seperated for run-time optimization
					isDestinationValid = movePiece->isDestinationValid(pos1, pos2, canEnPassant);
				}
			}

			// General Movement Checks
			if (isDestinationValid) {
				if (!pathBlocked || movePiece->getType() == 'n') {
						
					if (isOwnKingInCheck) {
						Piece* temp = destPiece;

						// Temporarily apply the move to see if it gets player out of check
						this->board[pos2] = this->board[pos1];
						this->board[pos1] = this->empty;

						bool isStillInCheck = true;
						if (movePiece->getTeam() == 'w') { isStillInCheck = isInCheck(this->wKing); }
						else { isStillInCheck = isInCheck(this->bKing); }

						if (isStillInCheck) { 
							// Doesn't get out of check, reset the board
							this->board[pos1] = this->board[pos2];
							this->board[pos2] = temp;
							return false;
						}
						else { 
							// Still have to reset the board, because movePiece() will still move the piece after this
							this->board[pos1] = this->board[pos2];
							this->board[pos2] = temp;
							return true;
						}
					}

					else { 
						Piece* temp = destPiece;
						this->board[pos2] = this->board[pos1];
						this->board[pos1] = this->empty;

						bool isNowInCheck = true;
						if (movePiece->getTeam() == 'w') { isNowInCheck = isInCheck(this->wKing); }
						else { isNowInCheck = isInCheck(this->bKing); }

						if (isNowInCheck) { 
							// Still have to reset the board, because movePiece() will still move the piece after this
							this->board[pos1] = this->board[pos2];
							this->board[pos2] = temp;
							return false; 
						}
						else { 
							// Still have to reset the board, because movePiece() will still move the piece after this
							this->board[pos1] = this->board[pos2];
							this->board[pos2] = temp;
							return true; 
						}
					}
				}
			}
		}
		else { return false; }
	}

	return false;
}

bool Chessboard::canCastle(int& pos_king, int& pos_rook) {
	Piece* king = this->board[pos_king];
	Piece* rook = this->board[pos_rook];

	if (king->getTeam() == 'w') {
		if (wKingMoved || wRook1Moved || wRook2Moved) { return false; }
		else if (isPathBlocked(pos_king, pos_rook)) { return false; }
		else {
			if (pos_rook % 10 == 2) { // Are we dealing with A file Rook?
				this->board[24] = this->wKing;
				this->board[25] = this->wRook;

				this->board[22] = this->empty;
				this->board[26] = this->empty;

				if (isInCheck(king)) { // if the Castling results in the king being in check it can't happen, reset
					// reset positions
					this->board[26] = this->wKing;
					this->board[22] = this->wRook;

					this->board[24] = this->empty;
					this->board[25] = this->empty;

					return false;
				}
				else { return true; }
			}
			else {
				this->board[28] = this->wKing;
				this->board[27] = this->wRook;

				this->board[26] = this->empty;
				this->board[29] = this->empty;

				if (isInCheck(king)) {
					// reset positions
					this->board[26] = this->wKing;
					this->board[29] = this->wRook;

					this->board[28] = this->empty;
					this->board[27] = this->empty;

					return false;
				}
				else { return true; }
			}
		}
	}
	else {
		if (bKingMoved || bRook1Moved || bRook2Moved) { return false; }
		else if (isPathBlocked(pos_king, pos_rook)) { return false; }
		else {
			if (pos_rook % 10 == 2) { // Are we dealing with A file Rook?
				this->board[94] = this->bKing;
				this->board[95] = this->bRook;

				this->board[92] = this->empty;
				this->board[96] = this->empty;

				if (isInCheck(king)) {
					// reset positions
					this->board[96] = this->bKing;
					this->board[92] = this->bRook;

					this->board[94] = this->empty;
					this->board[95] = this->empty;

					return false;
				}
				else { return true; }
			}
			else {
				this->board[98] = this->bKing;
				this->board[97] = this->bRook;

				this->board[96] = this->empty;
				this->board[99] = this->empty;

				if (isInCheck(king)) {
					// reset positions
					this->board[96] = this->bKing;
					this->board[99] = this->bRook;

					this->board[98] = this->empty;
					this->board[99] = this->empty;

					return false;
				}
				else { return true; }
			}
		}
	}

	return false;
}

void Chessboard::checkEnPassant(int& pos1, int& pos2) {
	if (canEnPassant && this->board[pos2]->getType() == 'p' && pos2 == enPassantPos) {
		this->board[enPassantPawnPos] = empty;
	}
	if (this->board[pos2]->getType() == 'p') {
		if (pos2 - pos1 == 20) {
			canEnPassant = true;
			enPassantPos = pos2 - 10;
			enPassantPawnPos = pos2;
		}
		else if (pos2 - pos1 == -20) {
			canEnPassant = true;
			enPassantPos = pos2 + 10;
			enPassantPawnPos = pos2;
		}
		else {
			canEnPassant = false;
			enPassantPos = 0;
			enPassantPawnPos = 0;
		}
	}
	
}

bool Chessboard::isPathBlocked(int& pos1, int& pos2) {
	int distance = pos2 - pos1;
	int direction = 0;
	std::array<int, 8> validDirections = { -11, -10, -9, 9, 10, 11, -1, 1 }; // -1 & 1 purposely at back of array so they are last to be tested

	for (const auto& move : validDirections) {
		if (distance / move > 0 && distance % move == 0) {
			direction = move;
			break; // Stops the for loop as soon as direction is found.
		}
	}

	int posCheck = pos1 + direction; // Moves to the first initial position on the board to check

	if (posCheck == pos2) { return false; } // If the initial position being checked is the destination, doesn't matter if there's a piece in the way, just move
	
	bool test = this->board[posCheck]->getTeam() != '0';
	bool test2 = this->board[posCheck]->getTeam() != this->empty->getTeam();
	bool test3 = this->board[posCheck]->getTeam() == '0';
	bool test4 = this->board[posCheck]->getTeam() == 'b';
	while (posCheck != pos2) {
		test = this->board[posCheck]->getTeam() != '0';
		test2 = this->board[posCheck]->getTeam() != this->empty->getTeam();
		test3 = this->board[posCheck]->getTeam() == '0';
		test4 = this->board[posCheck]->getTeam() == 'b';

		if (this->board[posCheck]->getTeam() != '0') { return true; } // If the checked position on the board is not empty the path is blocked
		posCheck += direction;
	}

	return false;
}

bool Chessboard::isInCheck(Piece* king) {
	// Assume Piece* king is actually a king piece

	// Find the position of the king
	int pos_king = findPiece(king);
	
	Piece* pieceToCheck;

	// Check knight attack locations
	for (int pos_relative : this->possKnightMoves) {
		
		int pos_knight = pos_king + pos_relative;
		pieceToCheck = this->board[pos_knight];

		if (!isPosOutOfBounds(pos_knight)) {
			if (pieceToCheck->getType() == 'n' && pieceToCheck->getTeam() != king->getTeam()) {
				if (pieceToCheck->isDestinationValid(pos_knight, pos_king)) { return true; }
			}
		}
	}

	for (std::array<int, 7> arr : this->kCheck) {
		for (int pos_relative : arr) {

			int pos_piece = pos_king + pos_relative;
			pieceToCheck = this->board[pos_piece];

			if (isPosOutOfBounds(pos_piece)) { break; }
			else if (pieceToCheck->getTeam() == king->getTeam()) { break; } // Path is blocked by piece on same team, no need to check the rest

			else if (pieceToCheck->getType() != this->empty->getType() && pieceToCheck->getTeam() != king->getTeam()) {

				if (pieceToCheck->isDestinationValid(pos_piece, pos_king)) { return true; }
				// Up until this piece, all spaces between it and the king are empty, so there is no need to call isPathBlocked()

				break; // The piece doesn't check the king and blocks the rest of the path
			}
		}
	}

	return false;
}

bool Chessboard::isInStalemate(Piece* king) {
	// Assume Piece* king is actually a king piece
	
	// Find the position of the king
	int pos_king = findPiece(king);

	for (int move : this->possKingMoves) {
		int pos_dest = pos_king + move;

		if (isMoveValid(pos_king, pos_dest)) { return false; } // If the king can move not in stalemate, return false
	}

	char teamToCheck = '_';
	if (this->whiteTurn) { teamToCheck = 'b'; }
	else { teamToCheck = 'w'; }

	if (hasAvailableMove(teamToCheck)) { return false; }
	std::cout << "got here\n";

	// At this point nothing can move so now just make sure that the king isn't in check
	if (isInCheck(king)) { return false; }

	std::cout << "\nStalemate! \n";
	return true;
}

bool Chessboard::isInCheckmate(Piece* king) {
	// Assume Piece* king is actually a king piece

	// Find the position of the king
	if (!isInCheck(king)) { return false; }

	int pos_king = findPiece(king);

	for (int move : possKingMoves) {
		int pos_dest = pos_king + move;
		if (isMoveValid(pos_king, pos_dest)) { return false; } // If the king can move, not in checkmate, return false
	}

	char teamToCheck = king->getTeam();
	// Is there a move such that the king is no longer in check?
	if (hasAvailableMove(teamToCheck)) { return false; }

	std::cout << "\nCheckmate! \n";
	return true;
}

// ********** MISC METHODS ********** //
int Chessboard::coordToIndex(std::string coordinate) {
	coordinate[0] = std::tolower(coordinate[0]);

	int tens = 0;
	int ones = 0;

	switch (coordinate[0]) {
	case 'a':
		ones = 2;
		break;
	case 'b':
		ones = 3;
		break;
	case 'c':
		ones = 4;
		break;
	case 'd':
		ones = 5;
		break;
	case 'e':
		ones = 6;
		break;
	case 'f':
		ones = 7;
		break;
	case 'g':
		ones = 8;
		break;
	case 'h':
		ones = 9;
		break;
	}

	switch (coordinate[1]) {
	case '1':
		tens = 20;
		break;
	case '2':
		tens = 30;
		break;
	case '3':
		tens = 40;
		break;
	case '4':
		tens = 50;
		break;
	case '5':
		tens = 60;
		break;
	case '6':
		tens = 70;
		break;
	case '7':
		tens = 80;
		break;
	case '8':
		tens = 90;
		break;
	}

	return (tens + ones);
}

int Chessboard::findPiece(Piece* piece) {
	for (int i = this->m_boardStart; i <= this->m_boardEnd; ++i) {
		if (this->board[i] == piece) { return i; }
	}

	return -1;
}

bool Chessboard::isPosOutOfBounds(int& pos) {
	if (pos < this->m_boardStart || pos > this->m_boardEnd) { return true; }
	return false;
}

bool Chessboard::hasAvailableMove(char& teamToCheck) {

	for (int space = this->m_boardStart; space <= this->m_boardEnd; ++space) {

		int pos_dest = 0;

		if (this->board[space]->getTeam() == teamToCheck) {

			switch (this->board[space]->getType()) {
			case 'p':
				for (int i : this->possPawnMoves) {
					pos_dest = space + i;
					if (isMoveValid(space, pos_dest)) { return true; }
				}
				break;

			case 'r':
				for (int i : this->possRookMoves) {
					pos_dest = space + i;
					if (isMoveValid(space, pos_dest)) { return true; }
				}
				break;

			case 'n':
				for (int i : this->possKnightMoves) {
					pos_dest = space + i;
					if (isMoveValid(space, pos_dest)) { return true; }
				}
				break;

			case 'b':
				for (int i : this->possBishopMoves) {
					pos_dest = space + i;
					if (isMoveValid(space, pos_dest)) { return true; }
				}
				break;

			case 'q':
				for (int i : this->possQueenMoves) {
					pos_dest = space + i;
					if (isMoveValid(space, pos_dest)) { return true; }
				}
				break;

			case 'k':
				// Ignore kings already checked; Actually might not even need this case, I'll check later
				break;
			}
		}
	}
	
	return false;
}