#include<iostream>
#include"Directions.hpp"
#include"Coordinates.hpp"
#include"Game.hpp"
#include<list>
#include <queue>


Game::Game(int map_width_, int map_length_)
{
    
    map_ = new game_material *[MAP_LENGTH];

    for (int i = 0 ; i < MAP_LENGTH ; i++)
        map_[i] = new game_material[MAP_WIDTH]; 

    for (int i = 0 ; i < MAP_LENGTH; i++)
        for(int j = 0 ; j < MAP_WIDTH; j++)
            map_[i][j] = EMPTY;
}
void Game::set_game_map(Snake& snake_head)
{
    list<pair<int,int>> snakeCoords = snake_head.get_snake_coords();
    for (int i = 0 ; i < MAP_LENGTH; i++)
        for(int j = 0 ; j < MAP_WIDTH; j++)
            map_[i][j] = EMPTY;

    for (const auto& coord : snakeCoords) 
    {
        //cout << "Row: " << coord.first << ", Column: " << coord.second << endl;
        map_[coord.first][coord.second] = SNAKE;
    }
}
		
game_material** Game::get_game_map()
{
    return map_;
}
	