#include "world.h"

void World::add_polygon(Polygon p)
{
	m_polygons.push_back(p);
}

void World::add_color(Vector3<unsigned int> color)
{
	m_colors.push_back(color);
}

void World::set_colors(std::vector<Vector3<unsigned int>> colors)
{
	m_colors = colors;
}

void World::set_polygons(std::vector<Polygon> polygons)
{
	m_polygons = polygons;
}

void World::draw()
{

	//std::cerr << m_polygons.size() << '\n';
	unsigned int poly_index;
	for(poly_index = 0; poly_index < m_polygons.size(); ++poly_index)
	{
		DrawLib::drawCircle(5, m_polygons[poly_index][0], true);
	}

	/*glBegin(GL_TRIANGLES);
	{
		glColor3ub(255, 0, 255);
		glVertex2f(50, 0);
		glColor3ub(0, 255, 0);
		glVertex2f(-50, 0);
		glColor3ub(0, 255, 255);
		glVertex2f(50, 50);
	}
	glEnd();

	glColor3ub(255, 255, 0);
	DrawLib::drawCircle(50, Vector2<int>(40, 90), true); */
}

unsigned int World::polygons()
{
	return m_polygons.size();
}

Vector3<unsigned int> World::get_color(unsigned int index)
{
	return m_colors[index - 1];
}
