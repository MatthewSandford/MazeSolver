#pragma once

#include <vector>
#include <assert.h>
#include <iostream>

#include "vector2.h"

class Maze_node
{
public:

	Maze_node() : distance(), position(), children(), parent() {};
	Maze_node(Vector2<int> new_position) : distance(), position(new_position), children(), parent() {};
	~Maze_node() {};

	//Mutators
	void set_distance(const double new_distance);
	void set_position(const Vector2<int> new_position);

	//Accessors
	double get_distance() const { return distance; };
	Vector2<int> get_position() const { return position; };

	//Outout stream
	friend std::ostream& operator << (std::ostream& out, Maze_node& node);

	Maze_node* parent;
	std::vector<Maze_node*> children;

protected:

private:

	double distance;
	Vector2<int> position;

};