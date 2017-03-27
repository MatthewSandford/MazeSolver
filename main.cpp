#include "maze_solver.h"

int main(int argc, char** argv)
{
	assert(("Incorrect number of argument.", argc == 2));

	Maze_solver solver;
	solver.maze.load_maze(argv[1]);
	solver.solve(1);

	system("PAUSE");
}