#pragma once

template <class T>
class Vector2
{
public:

	Vector2() : x(), y() {};
	Vector2(T new_x, T new_y) : x(new_x), y(new_y) {}
	~Vector2() {};

	friend std::ostream& operator << (std::ostream& out, Vector2& vector) 
	{
		out << "(" << vector.x << "," << vector.y << ")" << std::endl;
		return out;
	};

	T x;
	T y;

protected:

private:

};
