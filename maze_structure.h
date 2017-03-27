#pragma once

#include "Maze_node.h"

class Maze_structure
{
public:

	Maze_structure() : root(), end(), leaf_nodes() {};
	~Maze_structure() { delete_structure(root); };

	Maze_node* root;
	Maze_node* end;
	std::vector<Maze_node*> leaf_nodes;

protected:

private:

	//Clean up structure
	void delete_structure(Maze_node* node_ptr);

};