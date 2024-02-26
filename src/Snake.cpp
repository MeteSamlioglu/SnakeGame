#include<iostream>
#include"Snake.hpp"
#include"SnakeObject.hpp"
#include"Directions.hpp"
#include"Coordinates.hpp"

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

bool Snake::isEmpty() const {
    return head == nullptr;
}

void Snake::increaseLength()
{
    Directions dir = tail->data.getActiveDirection();
    Coordinates* coord = tail->data.getCoordinates();
    SnakeObject object(coord->row, coord->column, dir); // Initialize with default values

    switch(dir) {
        case LEFT:
            object = SnakeObject(coord->row, coord->column + 1, dir); // Initialize inside the case
            this->insertAtEnd(object);
            break;
            
        case RIGHT:
            object = SnakeObject(coord->row, coord->column - 1, dir);
            this->insertAtEnd(object);
            break;
            
        case UP:
            object = SnakeObject(coord->row + 1, coord->column, dir);
            this->insertAtEnd(object);
            break;
            
        case DOWN:
            object = SnakeObject(coord->row - 1, coord->column, dir);
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
    
    if(is_move_catched == true)
    {	
        cout<<"Move is made";	
                                
        while(temp != nullptr)
        {
            temp->data.setActiveMove(global_direction, head->data.getCoordinates());
            
            //set_future_move(global_direction);
            
            //cout<<"Move Coords "<<temp->data.getMove().getMoveCoordinates()->row<<" "<<temp->data.getMove().getMoveCoordinates()->column<<" ";
            
            //cout<<"Move Directions "<<temp->data.getMove().getMoveCoordinates( )<<endl;
            
            change_the_coordinates(temp->data.getActiveDirection(), temp->data);
            
            temp = temp->next;
        }
        
        is_move_catched = false;
    }
    else
    {
        while(temp != nullptr)
        {
            temp->data.setActiveMove(global_direction, head->data.getCoordinates());
            change_the_coordinates(temp->data.getActiveDirection(), temp->data);
            temp = temp->next;
        }
    }
}

Directions Snake::get_head_direction() const
{
    return head->data.getActiveDirection();
}

void Snake::change_the_coordinates(Directions move, SnakeObject& obj)
{
    Coordinates* coord = obj.getCoordinates();
    Coordinates* moveAt = obj.getMove().getMoveCoordinates();
    Directions directionMove = obj.getMove().getDirectionCoordinates();
    Directions nextMove;
    // cout<<"Move Coords "<<obj.getMove().getMoveCoordinates()->row<<" "<<obj.getMove().getMoveCoordinates()->column<<" ";
    // cout<<"Move Directions "<<obj.getMove().getMoveCoordinates( )<<endl;
    // obj.removeLastMove();
    
    if(coord->row == moveAt->row && coord->column == moveAt->column)
    {
        nextMove = directionMove;
        obj.removeLastMove();
    }
    else
    {
        nextMove = move;
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
        break;

    }
    
}
