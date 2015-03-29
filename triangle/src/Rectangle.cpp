/*
 * Rectangle
 *
 * File: 	Rectangle.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Jan 30 2015
 */

#include "Rectangle.hpp"

Rectangle::Rectangle()
{
	m_top_left = glm::vec3(0, 1, 1);
	m_bottom_right = glm::vec3(1, 0, 1);
}


Rectangle::Rectangle(glm::vec2 top_left, glm::vec2 bottom_right)
{
	m_top_left = glm::vec3(top_left[0], top_left[1], 1);
	m_bottom_right = glm::vec3(bottom_right[0], bottom_right[1], 1);
}

Rectangle::Rectangle( float x, float y, float w, float h)
{
	m_top_left = glm::vec3(x, y + h, 1);
	m_bottom_right = glm::vec3(x + w, y, 1);
}


float Rectangle::area()
{
	float width = abs(m_bottom_right[0] - m_top_left[0]);
	float height = abs(m_top_left[1] - m_bottom_right[1]);
	return width * height;
}

float Rectangle::perimeter()
{
	float width = abs(m_bottom_right[0] - m_top_left[0]);
	float height = abs(m_top_left[1] - m_bottom_right[1]);

	return (width + height) * 2.f;
}

float Rectangle::height()
{
	return abs(m_top_left[1] - m_bottom_right[1]);
}

float Rectangle::width()
{
	return abs(m_bottom_right[0] - m_top_left[0]);
}
