#include "maze_solver.h"

//Function that selects the algorithm to use: only one algorithm curently
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
	std::vector<std::tuple<Vector2<int>, double>> moves = available_moves(location);

	//Sort the moves by their distance
	std::sort(begin(moves), end(moves), [](auto const &tup1, auto const &tup2) {return std::get<1>(tup1) < std::get<1>(tup2); });

	//Check if we found the exit
	for (auto& item : moves)
	{
		Vector2<int> move = std::get<0>(item);

		if (maze_solution.get_maze_value(move) == 2)
		{
			maze_solution.set_maze(move, 3);
			return 1;
		}
	}

	//Recersivly check each new moves available moves in order of closet point to goal
	for (std::tuple<Vector2<int>, double>& item : moves)
	{
		Vector2<int> move = std::get<0>(item);

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
std::vector<std::tuple<Vector2<int>, double>> Maze_solver::available_moves(Vector2<int> position)
{
	std::vector<std::tuple<Vector2<int>, double>> available_moves;

	int x, y;
	double distance;

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
				//Calculate distance from goal and return information as a tuple pair
				Vector2<int> move(x, y);
				distance = euclidean_distance(move, maze_solution.get_end());
				std::tuple<Vector2<int>, double> entry(move, distance);
				available_moves.push_back(entry);
			}
		}
	}

	return available_moves;
}

//Calculate euclidian distance between two Vector2s
double Maze_solver::euclidean_distance(Vector2<int> p1, Vector2<int> p2)
{
	double distance = sqrt( pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));

	return distance;
}