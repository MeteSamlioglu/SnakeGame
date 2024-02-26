#include<iostream>
#include"SnakeObject.hpp"
#include"Directions.hpp"
#include"Coordinates.hpp"
#include <queue>
#include <list>
using namespace std;
/* Snake.cpp*/
SnakeObject::SnakeObject(int row, int column)
{
	curr_coordinate = new Coordinates;
		
	curr_coordinate->row = row;
	
	curr_coordinate->column = column;		

	activeMove = RIGHT;
}

SnakeObject::SnakeObject(int row, int column, Directions dir_)
{
	curr_coordinate = new Coordinates;
		
	curr_coordinate->row = row;
	
	curr_coordinate->column = column;		

	activeMove = dir_;
}
void SnakeObject::setCoordinates(Coordinates& coord)
{
	curr_coordinate->row = coord.row;
	curr_coordinate->column = coord.column;
}
Coordinates* SnakeObject::getCoordinates() const
{
	return curr_coordinate;
}
void SnakeObject::updateCoordinates(Coordinates& temp)
{
	curr_coordinate->row = temp.row;
	curr_coordinate->column = temp.column;
}

Directions SnakeObject::getActiveDirection() const
{
	return activeMove;
}

void SnakeObject::setActiveMove(Directions dir_, Coordinates* coord)
{
	Coordinates nextCoord;
	Move nextMove = Move(dir_);
	
	nextCoord.row = coord->row;
	nextCoord.column = coord->column;
	
	nextMove.insertMove(dir_, nextCoord);
	directionsQueue.push(nextMove);	
	activeMove = dir_;
}
Move SnakeObject::getMove() const
{
	return directionsQueue.front();
}

void SnakeObject::removeLastMove()
{
	activeMove = directionsQueue.front().getDirectionCoordinates();
	directionsQueue.pop();
}