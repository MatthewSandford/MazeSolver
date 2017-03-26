#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <cstdio>
#include <ctime>

#include "vector2.h"

#define PI 3.14159265

class Maze
{
public:

	Maze() : start(), end(), maze_w(), maze_h(), maze_vector() {};
	Maze(std::string file) : start(), end(), maze_w(), maze_h(), maze_vector() { load_maze(file); };
	Maze(std::vector<std::vector<int>> input_maze) : start(), end(), maze_w(), maze_h(), maze_vector() { load_maze(input_maze); };
	Maze(const Maze& input_maze) : start(input_maze.start), end(input_maze.end), maze_w(input_maze.maze_w), maze_h(input_maze.maze_h), maze_vector(input_maze.maze_vector) {};
	~Maze() {};

	//Load from file
	void load_maze(std::string file);

	//Accessors
	int get_width() { return maze_w; }
	int get_height() { return maze_h; }

	Vector2<int> get_start() { return start; }
	Vector2<int> get_end() { return end; }

	std::vector<std::vector<int>> get_maze() { return maze_vector; };

	int get_maze_value(Vector2<int> position) { return maze_vector[position.y][position.x]; };
	int get_maze_value(int x, int y) { return maze_vector[y][x]; };

	//Mutators
	void set_maze(Vector2<int> position, int value) { maze_vector[position.y][position.x] = value; };

	//Print functions
	void print_maze_info();
	friend std::ostream& operator << (std::ostream& out, Maze& maze_object);

protected:

private:

	std::vector<std::vector<int>> maze_vector;
	Vector2<int> start, end;
	int maze_w, maze_h;
};