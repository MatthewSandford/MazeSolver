#include "maze_solver.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Incorrect number of argument.\nPlease try again!!!" << std::endl;
	}
	else
	{
		Maze_solver solver;
		solver.maze.load_maze(argv[1]);
		solver.solve(1);
	}

	while (1)
	{

	}
}