#ifndef Game_hpp
#define Game_hpp
#define MAP_WIDTH 32
#define MAP_LENGTH 16
#include"Snake.hpp"
#include"SnakeObject.hpp"
enum game_material {WALL, EMPTY, SNAKE, TARGET };

class Game
{
	public:
		Game(int map_width_, int map_length_);
		void set_game_map(Snake& snake_head);
		
		game_material** get_game_map();
	private:
		game_material **map_;
};

#endif