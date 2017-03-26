#include  "maze.h"

void Maze::load_maze(std::string file)
{
	std::ifstream openFile(file.c_str());
	std::string line;
	int row(0);

	//Loop through lines in input file
	while (getline(openFile, line))
	{
		std::vector<int> temp;

		//Loop through line string
		for (int column(0) ; column < line.length() ; column++)
		{
			int char_int = line[column] - '0';

			temp.push_back(char_int);

			//Check for a start or end character
			if (char_int == 2)
			{
				if (start.x == NULL)
				{
					start.x = column;
					start.y = row;
				}
				else
				{
					end.x = column;
					end.y = row;
				}
			}
		}
		maze_vector.push_back(temp);
		row++;
	}

	maze_w = maze_vector[0].size();
	maze_h = maze_vector.size();
}

void Maze::load_maze(std::vector<std::vector<int>> input_maze)
{
	maze_vector = input_maze;

	maze_w = input_maze[0].size();
	maze_h = input_maze.size();
}

std::ostream& operator << (std::ostream& out, Maze& maze_object)
{
	//Loop through maze and print
	for (auto&row : maze_object.maze_vector)
	{
		for (auto&value : row)
		{
			switch (value)
			{
			case 0:
				out << ' ';
				break;
			case 1:
				out << '#';
				break;
			case 2:
				out << 'X';
				break;
			default:
				out << '-';
				break;
			}
		}
		out << std::endl;
	}

	return out;
}

void Maze::print_maze_info()
{
	std::cout << "Start: " << start.x << " " << start.y << std::endl;
	std::cout << "End: " << end.x << " " << end.y << "\n" << std::endl;

	std::cout << "Width: " << maze_w << std::endl;
	std::cout << "Height: " << maze_h << std::endl;
}