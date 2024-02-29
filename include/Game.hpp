#ifndef Game_hpp
#define Game_hpp
#define MAP_WIDTH 32
#define MAP_LENGTH 16
#include"Snake.hpp"
#include"SnakeObject.hpp"
enum game_material {WALL, EMPTY, SNAKE, TARGET};

class Game
{
	public:
		Game(int map_width_, int map_length_);
		
		bool set_game_map(Snake& snake_head, bool update_target);
		
		void reflesh_target(Snake& snake_head);
		
		game_material** get_game_map();
		
		bool isTargetOnSnake(Snake& snake_head, int row, int column) const;
		
		bool isTargetEaten(Snake& snake, int target_row, int target_column) const;
	
	private:
		game_material **map_;
		int map_width;
		int map_length;
		int target_row;
		int target_column;
	
};

#endif