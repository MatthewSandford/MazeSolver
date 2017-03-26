#pragma once

#include <windows.h>

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

	int recersive_step(Vector2<int> location);
	std::vector<Vector2<int>> available_moves(Vector2<int> position);
};
