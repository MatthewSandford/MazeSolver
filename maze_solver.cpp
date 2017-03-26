#include "maze_solver.h"

void Maze_solver::solve(int solve_type)
{
	maze_solution = maze;

	std::cout << "Solution\n" << std::endl;

	std::clock_t start_time(std::clock());

	switch (solve_type)
	{
	case 0:

		recersive_step(maze.get_start());
	break;
	default:

	break;
	}

	std::clock_t end_time(std::clock());

	std::cout << maze_solution << std::endl;

	double  duration = (end_time - start_time) / (double)CLOCKS_PER_SEC;
	std::cout << "Algorithm Time: " << duration << "s" << std::endl;
}

int Maze_solver::recersive_step(Vector2<int> location)
{
	maze_solution.set_maze(location, 3);

	//Find mabailable moves from position
	std::vector<Vector2<int>> moves = available_moves(location);

	//Check if we found the exit
	for (auto& move : moves)
	{
		if (maze_solution.get_maze_value(move) == 2)
		{
			maze_solution.set_maze(move, 3);
			return 1;
		}
	}

	//Recersivly check each new moves available moves
	for (Vector2<int>& move : moves)
	{
		//Check if finished
		bool finished = recersive_step(move);

		if (finished)
		{
			return 1;
		}
		else
		{
			//Destroy dead end path
			maze_solution.set_maze(move, 0);
		}
	}

	return 0;
}

//Function to find all available moves from given position in maze
std::vector<Vector2<int>> Maze_solver::available_moves(Vector2<int> position)
{
	std::vector<Vector2<int>> available_moves;

	int x, y;

	//Check all cells 
	for (float angle(0); angle<360; angle += 90)
	{
		x = position.x + (int)sin(angle*PI / 180.0);
		y = position.y + (int)cos(angle*PI / 180.0);

		//Check cell within bounds 
		if (x < maze_solution.get_width() && y < maze_solution.get_height() && x >= 0 && y >= 0)
		{
			//Check its an empty cell or exit cell 
			if (maze_solution.get_maze_value(x,y) == 0 || maze_solution.get_maze_value(x, y) == 2)
			{
				available_moves.push_back(Vector2<int>(x, y));
			}
		}
	}

	return available_moves;
}