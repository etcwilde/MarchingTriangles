#ifndef RECT_H
#define RECT_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cmath>

using namespace glm;

class Rectangle
{
	public:
		// 1 x 1
		Rectangle();
		Rectangle(vec2 top_left, vec2 bottom_right);
		// x, y -- bottom left corner
		Rectangle(float x, float y, float w, float h);

		float area();
		float perimeter();
		float height();
		float width();

	private:
		// Homogeneous coordinate system
		vec3 m_top_left;
		vec3 m_bottom_right;
};

#endif //RECT_H
