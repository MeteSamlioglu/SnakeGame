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
#include <random>
#include <chrono>
#include <atomic>

#define MAP_WIDTH 32
#define MAP_LENGTH 16

using namespace std;


Directions global_direction = RIGHT;

bool is_move_catched = false;

bool update_target = false;
//bool is_quit = false;
std::atomic<bool> is_quit(false);

void threadFunction() {
    // Change terminal settings to non-canonical mode
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    char c;
    while (is_quit != true) {
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

void reflesh_target()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    while(is_quit != true) 
    {
        update_target = true;
        std::this_thread::sleep_for(std::chrono::seconds(8));
    }
}

SnakeObject headObject = SnakeObject(4, 4); // Fix

void display_map(Game game_);
void game( );
void apply_move(Directions move);
void update_terminal(Game game_);

std::thread t1(threadFunction);
std::thread t2(reflesh_target);
int main() {
        

    
    game();
    
    t1.join();
    t2.join();
    
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

    
    while(is_quit!= true)
    {

        update_terminal(game_); 

        snake_.set_active_move(global_direction, is_move_catched);
        
        if(game_.set_game_map(snake_, update_target) == false)
        {
            is_quit = true;
            break;
        }       
        if(is_move_catched)
            is_move_catched = false;
        if(update_target)
        {
            update_target = false;
        }
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
            if(map_[i][j] == SNAKE)
                cout<<"*";
            if(map_[i][j] == TARGET)
                cout<<"O";
        }
        cout<<endl;
    }
}		

void update_terminal(Game game_)
{
        cout<<endl<<endl;
        display_map(game_);
        usleep(150000);
        //std::system("cls");
        std::system("clear");
}

