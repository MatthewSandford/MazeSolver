#pragma once

#include <math.h> 
#include <windows.h>
#include <algorithm>

#include "maze.h"
#include "maze_node.h"
#include "maze_structure.h"

class Maze_solver
{
public:

	Maze_solver() : maze(), maze_solution() {};
	Maze_solver(Maze input_maze) : maze(input_maze), maze_solution() {};
	void solve(int solve_type = 0);

	Maze maze;
	Maze maze_solution;

protected:

private:

	//First algorithm
	Maze_structure* recersive_step(Maze_structure* maze_ptr);

	//A*algorithm
	Maze_structure* A_recersive_step(Maze_structure* maze_ptr);

	//Find available moves from a position
	std::vector<Maze_node*> available_moves(Maze_node* node_ptr);

	//Uses maze_strcutre to print solution
	void find_path(Maze_structure* maze_ptr);

	//Helper function
	double euclidean_distance(const Vector2<int> p1, const Vector2<int> p2);
};
