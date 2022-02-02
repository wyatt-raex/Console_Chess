#include "Piece.h"

//Private Methods
void Piece::setId(std::string id) { this->id = id; }

void Piece::setName(std::string name) { this->name = name; }

void Piece::setTeam(char team) { this->team = team; }

void Piece::setType(char type) { this->type = type; }

//Public Methods
Piece::Piece(char type, std::string id, std::string name, char team) {
	this->setId(id);
	this->setName(name);
	this->setTeam(team);
	this->setType(type);
}

std::string Piece::getId() { return this->id; }

std::string Piece::getName() { return this->name; }

char Piece::getTeam() { return this->team; }

char Piece::getType() { return this->type; }
