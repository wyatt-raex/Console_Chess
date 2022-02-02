#pragma once
#include "pch.h"

#include <iostream>
#include <string>

class Piece
{
private:
	std::string name = "empty";
	std::string id = "__";
	char team = '0';
	char type = '0';

	void setId(std::string id);
	void setName(std::string name);
	void setTeam(char team);
	void setType(char type);

public:
	Piece(char type = '0', std::string id = "__", std::string name = "empty",
		char team = '0');

	std::string getId();
	std::string getName();
	char getTeam();
	char getType();

	virtual bool isDestinationValid(int& source, int& destination) = 0;
	virtual bool isDestinationValid(int& source, int& destination, bool& isPieceAtDest) = 0;
};

