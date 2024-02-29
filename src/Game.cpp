#include <iostream>
#include"Directions.hpp"
#include"Coordinates.hpp"
#include"Game.hpp"
#include<list>
#include <queue>
#include <random>
#include <chrono>
#include <unistd.h>
Game::Game(int map_width_, int map_length_)
{
    
    map_ = new game_material *[map_length_];

    for (int i = 0 ; i < map_length_ ; i++)
        map_[i] = new game_material[map_width_]; 

    for (int i = 0 ; i < map_length_; i++)
        for(int j = 0 ; j < map_width_; j++)
            map_[i][j] = EMPTY;

    map_width = map_width_;
    map_length = map_length_;
    target_column = 3;
    target_row = 3;
}

bool Game::isTargetOnSnake(Snake& snake_head, int row, int column) const
{
    return snake_head.isPointOnSnake(row, column);    
}

void Game::reflesh_target(Snake& snake_head)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    while(1)
    {
        std::uniform_int_distribution<int> row(0, map_length - 2);
        std::uniform_int_distribution<int> column(0, map_width - 2);
        target_row = row(gen);
        target_column = column(gen);
        if(isTargetOnSnake(snake_head, target_row, target_column) == false)
            break;
    }
}

bool Game::isTargetEaten(Snake& snake, int target_row, int target_column) const
{
    return snake.isHeadOnTarget(target_row, target_column);
}

bool Game::set_game_map(Snake& snake_head, bool update_target)
{
    if(snake_head.isEatenItself())
    {
        cout<<"Game is Over";
        return false;
    }
    if(update_target)
    {
        reflesh_target(snake_head);
    }
    if(update_target == false && isTargetEaten(snake_head, target_row, target_column))
    {    
        snake_head.increaseLength(); // tail'ın movelarını da almalı sadece aktif move değil hepsini
        reflesh_target(snake_head);
    }
    list<pair<int,int>> snakeCoords = snake_head.get_snake_coords();
    for (int i = 0 ; i < MAP_LENGTH; i++)
        for(int j = 0 ; j < MAP_WIDTH; j++)
            map_[i][j] = EMPTY;

    for (const auto& coord : snakeCoords) 
    {
        //cout << "Row: " << coord.first << ", Column: " << coord.second << endl;
        map_[coord.first][coord.second] = SNAKE;
    }
    map_[target_row][target_column] = TARGET;
    
    return true;
}

		
game_material** Game::get_game_map()
{
    return map_;
}
	