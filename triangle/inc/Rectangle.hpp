/*
 * Rectangle
 *
 * File: 	Rectangle.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Jan 30 2015
 */

#ifndef RECT_H
#define RECT_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cmath>

using namespace glm;

/**
 * \class Rectangle
 * \brief Defines a 2D rectangle
 */

class Rectangle
{
	public:
		/**
		 * \brief Creates a 1x1 rectangle
		 */
		Rectangle();

		/**
		 * \brief creates a rectangle
		 *
		 * @param top_left Upper left-hand corner coordinate
		 * @param bottom_right Lower right-hand corner coordinate
		 */
		Rectangle(vec2 top_left, vec2 bottom_right);
		/**
		 * \brief Creates a rectangle
		 *
		 * @param x Bottom left corner x coordinate
		 * @param y bottom left corner y coordinate
		 * @param w Width of the rectangle
		 * @param h Height of the rectangle
		 */
		Rectangle(float x, float y, float w, float h);

		/**
		 * \brief Returns the area of the rectangle
		 */
		float area();

		/**
		 * \brief Returns the perimeter of the rectangle
		 */
		float perimeter();

		/**
		 * \brief Returns the height of the rectangle
		 */
		float height();

		/**
		 * \brief Returns the width of the rectangle
		 */
		float width();

	private:
		// Homogeneous coordinate system
		vec3 m_top_left;
		vec3 m_bottom_right;
};

#endif //RECT_H
