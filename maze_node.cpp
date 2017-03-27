#include "maze_node.h"

void Maze_node::set_distance(double new_distance)
{
	assert(("Maze node distance set lower than 0", new_distance >= 0));
	distance = new_distance;
}

void Maze_node::set_position(Vector2<int> new_position)
{
	bool test = new_position.x >= 0 && new_position.y >= 0;
	assert(("Maze node distance set lower than 0", test));
	position = new_position;
}

std::ostream & operator<<(std::ostream & out, Maze_node & node)
{
	out << "Position: " << node.position << "Distance: " << node.distance << "Children: " << node.children.size() << std::endl;
	return out;
}
