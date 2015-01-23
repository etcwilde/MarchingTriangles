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

