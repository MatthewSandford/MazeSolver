#pragma once

#include "Maze_node.h"

class Maze_structure
{
public:

	Maze_structure() {};
	~Maze_structure() {};

	Maze_node* root;
	Maze_node* end;
	std::vector<Maze_node*> leaf_nodes;

protected:

private:

};