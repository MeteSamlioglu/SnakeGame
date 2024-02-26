#ifndef Move_hpp
#define Move_hpp
#include"Coordinates.hpp"
#include"Directions.hpp"

class Move
{
	public:
		Move(Directions dir_);
		void insertMove(Directions dir_, Coordinates& coord);
		void removeLastMove();
		Coordinates* getMoveCoordinates() const;
		Directions getDirectionCoordinates() const;

	private:
		Coordinates* moveAt;
		Directions direction_;
};

#endif