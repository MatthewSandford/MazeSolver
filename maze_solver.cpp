#include "maze_solver.h"

//Function that selects the algorithm to use: only one algorithm curently
void Maze_solver::solve(int solve_type)
{
	maze_solution = maze;

	std::cout << "Solution\n" << std::endl;

	std::clock_t start_time(std::clock());

	//Set up a maze structure
	Maze_structure* maze_ptr = new Maze_structure;

	//Initialize first node in structure
	Maze_node* root = new Maze_node;
	root->set_position(maze_solution.get_start());
	root->set_distance(euclidean_distance(maze_solution.get_start(), maze_solution.get_end()));
	maze_solution.set_maze(root->get_position(), 3);

	//Add first first node to structure
	maze_ptr->root = root;
	maze_ptr->leaf_nodes.push_back(root);

	//Call recursive algorithm
	switch (solve_type)
	{
	case 0:

		recersive_step(maze_ptr);

	break;
	case 1:

		A_recersive_step(maze_ptr);

	break;
	}
	
	find_path(maze_ptr);

	//Clean up structure
	delete maze_ptr;

	std::clock_t end_time(std::clock());

	std::cout << maze_solution << std::endl;

	double  duration = (end_time - start_time) / (double)CLOCKS_PER_SEC;
	std::cout << "Algorithm Time: " << duration << "s" << std::endl;
}

Maze_structure* Maze_solver::A_recersive_step(Maze_structure* maze_ptr)
{
	double minimum(0);
	Vector2<int> move;
	Maze_node* best_node(maze_ptr->root);

	//Search for the lowest distance leaf node
	for (int i(0); i < maze_ptr->leaf_nodes.size(); i++)
	{
		if (i == 0)
		{
			minimum = maze_ptr->leaf_nodes[i]->get_distance();
			best_node = maze_ptr->leaf_nodes[i];
		}
		else
		{
			if (maze_ptr->leaf_nodes[i]->get_distance() < minimum)
			{
				minimum = maze_ptr->leaf_nodes[i]->get_distance();
				best_node = maze_ptr->leaf_nodes[i];
			}
		}
	}

	//Find all possible moves for the best leaf node
	std::vector<Maze_node*> possible_moves(available_moves(best_node));

	//Loop through the possible moves and add them to the maze structures leaf nodes and parent node
	for (auto& new_move : possible_moves)
	{
		//Update maze object so we dont back track
		maze_solution.set_maze(new_move->get_position(), 3);

		new_move->parent = best_node;
		best_node->children.push_back(new_move);

		//Add node to maze structures leaf node vector
		maze_ptr->leaf_nodes.push_back(new_move);

		//Check if we have reached the end
		if (new_move->get_distance() == 0)
		{
			maze_ptr->end = new_move;
			return maze_ptr;
		}
	}

	//Remove last best position from leaf nodes 
	std::tuple<Vector2<int>, double> item;

	for (int i(0); i < maze_ptr->leaf_nodes.size(); i++)
	{
		if (maze_ptr->leaf_nodes[i]->get_position() == best_node->get_position())
		{
			maze_ptr->leaf_nodes.erase(maze_ptr->leaf_nodes.begin()+i);
		}
	}

	//Recursive call
	return A_recersive_step(maze_ptr);
}

Maze_structure* Maze_solver::recersive_step(Maze_structure* maze_ptr)
{
	//Find all possible moves for the best leaf node
	std::vector<Maze_node*> moves(available_moves(maze_ptr->leaf_nodes[0]));
	
	//Loop through the possible moves and add them to the maze structures leaf nodes and parent node
	for (auto& new_move : moves)
	{
		//Update maze object so we dont back track
		maze_solution.set_maze(new_move->get_position(), 3);

		new_move->parent = maze_ptr->leaf_nodes[0];
		maze_ptr->leaf_nodes[0]->children.push_back(new_move);

		//Add node to maze structures leaf node vector
		maze_ptr->leaf_nodes[0] = new_move;

		//Check if we have reached the end
		if (new_move->get_distance() == 0)
		{
			maze_ptr->end = new_move;
			return maze_ptr;
		}

		return A_recersive_step(maze_ptr);
	}
}

//Function to find all available moves from given position in maze
std::vector<Maze_node*> Maze_solver::available_moves(Maze_node* node_ptr)
{
	std::vector<Maze_node*> available_moves;

	int x, y;
	double distance;

	//Check all cells 
	for (float angle(0); angle<360; angle += 90)
	{
		x = node_ptr->get_position().x + (int)sin(angle*PI / 180.0);
		y = node_ptr->get_position().y + (int)cos(angle*PI / 180.0);

		//Check cell within bounds 
		if (x < maze_solution.get_width() && y < maze_solution.get_height() && x >= 0 && y >= 0)
		{
			//Check its an empty cell or exit cell 
			if (maze_solution.get_maze_value(x, y) == 0 || maze_solution.get_maze_value(x, y) == 2)
			{
				//Create a new node to add to the vector to return
				Maze_node* entry = new Maze_node;

				distance = euclidean_distance(Vector2<int>(x, y), maze_solution.get_end());

				entry->set_position(Vector2<int>(x, y));
				entry->set_distance(distance);

				available_moves.push_back(entry);
			}
		}
	}

	return available_moves;
}

//Function the tracks back through the maze structure to find our route
void Maze_solver::find_path(Maze_structure* maze_ptr)
{
	maze_solution = maze;

	Maze_node* node_ptr(maze_ptr->end);

	while (node_ptr->get_position() != maze_ptr->root->get_position())
	{
		maze_solution.set_maze(node_ptr->get_position(), 3);

		node_ptr = node_ptr->parent;
	}
}

//Calculate euclidian distance between two Vector2s
double Maze_solver::euclidean_distance(const Vector2<int> p1, const Vector2<int> p2)
{
	double distance = sqrt( pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));

	return distance;
}