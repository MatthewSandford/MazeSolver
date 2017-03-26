#pragma once

#include <math.h> 
#include <windows.h>
#include <algorithm>

#include "maze.h"

class Maze_solver
{
public:

	Maze_solver() {};
	Maze_solver(Maze input_maze) : maze(input_maze) {};
	void solve(int solve_type = 0);

	Maze maze;
	Maze maze_solution;

protected:

private:

	double euclidean_distance(Vector2<int> p1, Vector2<int> p2);
	int recersive_step(Vector2<int> location);
	std::vector<std::tuple<Vector2<int>, double>> available_moves(Vector2<int> position);
};
