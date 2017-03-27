#include "maze_structure.h"

void Maze_structure::delete_structure(Maze_node* node_ptr)
{ 
	if (node_ptr != NULL)
	{
		for (auto& child : node_ptr->children)
		{
			delete_structure(child);
		}
		delete(node_ptr);
	}
}
