#ifndef Snake_hpp
#define Snake_hpp

#include"SnakeObject.hpp"

class Snake {
private:
    struct Node {
        SnakeObject data;
        Node* next;
        Node(const SnakeObject& dataValue);
    };
    Node* head; 
	Node* tail;

public:
    Snake();
    ~Snake();

  	void insert(const SnakeObject& data);
	void insertAfterHead(const SnakeObject& data);
    void insertAtEnd(const SnakeObject& data);
	void clear();
	void increaseLength();
    void set_active_move(Directions global_direction, bool is_move_catched); 
	void change_the_coordinates(SnakeObject& obj);
    bool isEatenItself() const;
    bool isHeadOnTarget(int row, int column) const;
    bool compareWithHeadCoodinates(int row, int column) const;
    bool isPointOnSnake(int row, int column) const;
    bool isEmpty() const;
    list<pair<int,int>> get_snake_coords() const;
	Directions get_head_direction() const;

};
#endif