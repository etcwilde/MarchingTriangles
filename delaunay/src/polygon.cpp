#include "polygon.h"

Polygon::Polygon() {}
Polygon::~Polygon() {}

void Polygon::add_point(Vector2<int> pt, unsigned int color_index)
{
	m_points.push_back(pt);
	m_colors.push_back(color_index);
}

void Polygon::add_point(int x, int y, unsigned int color_index)
{
	m_points.push_back(Vector2<int>(x, y));
	m_colors.push_back(color_index);
}

unsigned int Polygon::size()
{
	return m_points.size();
}

unsigned int Polygon::color(unsigned int index)
{
	return m_colors[index];
}

Vector2<int> Polygon::operator[](const int index)
{
	return m_points[index % m_points.size()];
}


/*
 * Triangle
 */

Triangle::Triangle(Vector2<int>p1, Vector2<int>p2, Vector2<int>p3,
		unsigned int color1, unsigned int color2, unsigned int color3)
{
	m_points[0] = p1;
	m_points[1] = p2;
	m_points[2] = p3;

	m_colors[0] = color1;
	m_colors[1] = color2;
	m_colors[2] = color3;
}

void Triangle::draw()
{

	GLint data[] =
		{
		m_points[0].x, m_points[0].y,
		m_points[1].x, m_points[1].y,
		m_points[2].x, m_points[2].y
		};
}
