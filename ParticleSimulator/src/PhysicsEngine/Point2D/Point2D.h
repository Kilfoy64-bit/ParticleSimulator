#pragma once

#include "glm/glm.hpp"

struct Point2D {
	float x;
	float y;

	float distance(Point2D other) const
	{
		return sqrt(((x - other.x) * (x - other.x)) + ((y - other.y) + (y - other.y)));
	};

};