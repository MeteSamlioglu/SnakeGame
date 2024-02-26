#include<iostream>

#include"Directions.hpp"

#include"Move.hpp"
#include"Coordinates.hpp"


/* Move.cpp*/

Move::Move(Directions dir_)
{
	direction_ = dir_;
	moveAt = nullptr;
}

void Move::insertMove(Directions dir_, Coordinates& coord)
{
	moveAt = new Coordinates;
	moveAt->row = coord.row;
	moveAt->column = coord.column;
	direction_ = dir_;
}


Coordinates* Move::getMoveCoordinates() const
{
	return moveAt;
}

Directions Move::getDirectionCoordinates() const
{
	return direction_;
}
/*----------------------------------------------------*/
