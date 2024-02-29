#ifndef SnakeObject_hpp
#define SnakeObject_hpp
#include"Directions.hpp"
#include"Coordinates.hpp"
#include"Move.hpp"
#include <queue>
#include <list>
using namespace std;

class SnakeObject
{
	public:
		SnakeObject(int row, int column);
		SnakeObject(int row, int column, SnakeObject& tail);
		Coordinates* getCoordinates() const;
		void setCoordinates(Coordinates& coord);
		void updateCoordinates(Coordinates& temp);
		void setActiveMove(Directions dir_, Coordinates* coord);
		void setActiveDirection(Directions dir_);
		Directions getActiveDirection() const;
		Move getMove() const;
		bool isMoveQueueEmpty() const;
		queue<Move> getFutureMoves() const;
		void removeLastMove();
	private:
		Coordinates* curr_coordinate;
		queue<Move> directionsQueue;
		Directions activeMove;
		
};

#endif