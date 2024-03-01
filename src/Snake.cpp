#include<iostream>
#include"Snake.hpp"
#include"SnakeObject.hpp"
#include"Directions.hpp"
#include"Coordinates.hpp"
#include <termios.h>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

#define MAP_WIDTH 32
#define MAP_LENGTH 16

using namespace std;

Snake::Node::Node(const SnakeObject& dataValue) : data(dataValue), next(nullptr) {}

Snake::Snake() : head(nullptr), tail(nullptr) {}

Snake::~Snake() 
{
    clear();
}

void Snake::insert(const SnakeObject& data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = head; // If the list was empty, head and tail point to the same node
    }
}

void Snake::insertAfterHead(const SnakeObject& data) 
{
    if (head == nullptr) {
        insert(data); // If the list is empty, insert the node as the head
    } else {
        Node* newNode = new Node(data);
        newNode->next = head->next;
        head->next = newNode;
    }
}

void Snake::insertAtEnd(const SnakeObject& data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        tail = head;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void Snake::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

bool Snake::isEmpty() const 
{
    return head == nullptr;
}

bool Snake::isHeadOnTarget(int row, int column) const
{
    Coordinates* coord = head->data.getCoordinates();

    return (row == coord->row && column == coord->column) ? true : false;
}

bool Snake::isPointOnSnake(int row, int column) const
{
    Node* temp = head;
    
    while (temp != nullptr) {
        Coordinates *coord = temp->data.getCoordinates();
        
        if(row == coord->row && column == coord->column)
            return true;
        
        temp = temp->next;
    }

    return false;
}

bool Snake::compareWithHeadCoodinates(int row, int column) const
{
    Coordinates* head_coords = head->data.getCoordinates();
    return (head_coords->row == row && head_coords->column == column) ? true : false;
}

bool Snake::isEatenItself() const
{   
    Node* temp = head;
    temp = temp->next;
        
    while (temp != nullptr) 
    {
        Coordinates *coord = temp->data.getCoordinates();
        
        if(compareWithHeadCoodinates(coord->row, coord->column))
            return true;
        
        temp = temp->next;
    }
    return false;
}

void Snake::increaseLength()
{
    Directions dir = tail->data.getActiveDirection();
    Coordinates* coord = tail->data.getCoordinates();
    SnakeObject object(coord->row, coord->column, tail->data); // Initialize with default values
    
    switch(dir) {
        case LEFT:
            object = SnakeObject(coord->row, coord->column + 1, tail->data); // Initialize inside the case
            this->insertAtEnd(object);
            break;
            
        case RIGHT:
            object = SnakeObject(coord->row, coord->column - 1, tail->data);
            this->insertAtEnd(object);
            break;
            
        case UP:
            object = SnakeObject(coord->row + 1, coord->column, tail->data);
            this->insertAtEnd(object);
            break;
            
        case DOWN:
            object = SnakeObject(coord->row - 1, coord->column, tail->data);
            this->insertAtEnd(object);
            break;
    }
}
list<pair<int,int>> Snake::get_snake_coords() const {
    list<pair<int,int>> resultList;
    
    Node* temp = head;
    
    while (temp != nullptr) {
        Coordinates *coord = temp->data.getCoordinates();
        //cout << coord->row << "->"<<coord->column<<"->";
        resultList.push_back(make_pair(coord->row, coord->column));
        temp = temp->next;
    }
    return resultList;
}

void Snake::set_active_move(Directions global_direction, bool is_move_catched) 
{
    
    Node* temp = head;
    
    if(is_move_catched)
    {	        
       
        while(temp != nullptr)
        {
            temp->data.setActiveMove(global_direction, head->data.getCoordinates());
            
            temp = temp->next;
        }
        
    }
    
    temp = head;
    while(temp != nullptr)
    {
        change_the_coordinates(temp->data);
        temp = temp->next;
    }
    
}

Directions Snake::get_head_direction() const
{
    return head->data.getActiveDirection();
}

void Snake::change_the_coordinates(SnakeObject& obj)
{
    
    Coordinates* coord = obj.getCoordinates();

    Directions nextMove;

    if(obj.isMoveQueueEmpty())
    {
        nextMove = obj.getActiveDirection();
    }
    else
    {
        Coordinates* moveAt = obj.getMove().getMoveCoordinates();
        
        Directions directionMove = obj.getMove().getDirectionCoordinates();
        
        if(coord->row == moveAt->row && coord->column == moveAt->column)
        {
            nextMove = directionMove;
            obj.removeLastMove();
        }
        else
        {
            nextMove = obj.getActiveDirection();
        }
    }
 
    switch(nextMove)
    {
        case UP:		
            if(coord->row > 0)
            {
                coord->row = coord->row - 1;
                coord->column = coord->column;
            }
            else
            {
                coord->row = MAP_LENGTH - 1;
                coord->column = coord->column;
            }
            obj.setActiveDirection(UP);

            break;
        case DOWN:
            if(coord->row < MAP_LENGTH - 1) 
            {
                coord->row = coord->row + 1;
                coord->column = coord->column;
            }
            else
            {
                coord->row = 0;
                coord->column = coord->column;
            }
            obj.setActiveDirection(DOWN);

            break;
        case RIGHT:
            if(coord->column < MAP_WIDTH - 1)
            {
                coord->row = coord->row;
                coord->column = coord->column + 1;
            }	
            else
            {
                coord->row = coord->row;
                coord->column = 0; 
            }
            obj.setActiveDirection(RIGHT);
	
        break;
        case LEFT:
            if(coord->column > 0)
            {	
                coord->row = coord->row;
                coord->column  = coord->column - 1;
            }
            else
            {	
                coord->row  = coord->row;
                coord->column = MAP_WIDTH - 1;
            }
            obj.setActiveDirection(LEFT);
        break;
    }
    
}
