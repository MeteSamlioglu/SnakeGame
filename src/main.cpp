#include <iostream>
#include <cstdlib>
// #include <windows.h>
#include <ncurses.h>
#include <unistd.h>
#include <queue>
#include <list>
#include <thread>
#include <termios.h>

#include"Snake.hpp"
#include"Game.hpp"
#include"Directions.hpp"
#include"Coordinates.hpp"


#define MAP_WIDTH 32
#define MAP_LENGTH 16

using namespace std;


Directions global_direction = RIGHT;

bool is_move_catched = false;

bool is_quit = false;





void threadFunction() {
    // Change terminal settings to non-canonical mode
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    char c;
    while (1) {
        c = getchar();
        switch (c) {
            case 'W':
            case 'w': // Account for both uppercase and lowercase 'W'
                global_direction = UP;
                is_move_catched  = true;
                break;
            case 'S':
            case 's': // Account for both uppercase and lowercase 'S'
                global_direction = DOWN;
                is_move_catched  = true;
                break;
            case 'A':
            case 'a': // Account for both uppercase and lowercase 'A'
                global_direction = LEFT;
                is_move_catched  = true;
                break;
            case 'D':
            case 'd': // Account for both uppercase and lowercase 'D'
                global_direction = RIGHT;
                is_move_catched  = true;
                break;
            case '.':
                // Restore terminal settings and exit
                tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
                exit(0);
                break;
        }
        std::flush(std::cout); // Flush output stream
    }
}


SnakeObject headObject = SnakeObject(4, 4); // Fix

void display_map(Game game_);
void game( );
void apply_move(Directions move);
void update_terminal(Game game_);


int main() {
        
        
    std::thread t1(threadFunction);
    
    game();
    
    t1.join();

    return 0;
}


void game()
{
    Directions move;
    Snake snake_ = Snake();
    Game game_ = Game(MAP_WIDTH, MAP_LENGTH);
    snake_.insertAtEnd(headObject);
    snake_.increaseLength();
    snake_.increaseLength();
    snake_.get_snake_coords();
    
    while(is_quit!= true)
    {
        
        snake_.set_active_move(global_direction, is_move_catched);

        game_.set_game_map(snake_);

        update_terminal(game_);
    
        
    }
}


void display_map(Game game_)
{
    Coordinates* coord = headObject.getCoordinates();
    game_material** map_ = game_.get_game_map();

    for(int i = 0 ; i < MAP_LENGTH; i++)
    {
        for(int j = 0 ; j < MAP_WIDTH; j++)
        {
                
            if (map_[i][j] == EMPTY)
                cout<<" ";
            else if(map_[i][j] == SNAKE)
                cout<<"O";
        
        }
        cout<<endl;
    }
}		

void update_terminal(Game game_)
{
        cout<<endl<<endl;
        display_map(game_);
        usleep(50000);
        //std::system("cls");
        std::system("clear");
}

