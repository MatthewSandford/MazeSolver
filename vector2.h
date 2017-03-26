#pragma once

#include <iostream>

template <class T>
class Vector2
{
public:

	Vector2() : x(), y() {};
	Vector2(const T new_x, const T new_y) : x(new_x), y(new_y) {}
	~Vector2() {};

	bool operator == (const Vector2<T>& other) const;
	bool operator != (const Vector2<T>& other) const;

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

template <class T>
bool Vector2<T>::operator == (const Vector2<T>& other) const
{
	return x == other.x && y == other.y;
}

template <class T>
bool Vector2<T>::operator != (const Vector2<T>& other) const
{
	return x != other.x || y != other.y;
}