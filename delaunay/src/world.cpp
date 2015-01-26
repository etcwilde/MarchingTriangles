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
	//DrawLib::drawCircle(50, Vector2<int>(49, 90), true);
	unsigned int poly_index;
	for(poly_index = 0; poly_index < m_polygons.size(); ++poly_index) {
		// Draw lines
		glColor3ub(255, 255, 255);
		if (m_polygons[poly_index].size() >= 2)
		{
			DrawLib::drawLine(m_polygons[poly_index][m_polygons[poly_index].size() - 1],
					m_polygons[poly_index][0]);
			for (unsigned int i = 0; i < m_polygons[poly_index].size() - 1;
				++i)
			{
				DrawLib::drawLine(m_polygons[poly_index][i],
						m_polygons[poly_index][i + 1]);
			}
		}

		for (unsigned int i = 0; i < m_polygons[poly_index].size();
				++i)
		{
			unsigned int color = m_polygons[poly_index].color(i);
			Vector3<unsigned int> color_v = m_colors[color];
			glColor3ub(color_v.x, color_v.y, color_v.z);
			DrawLib::drawCircle(5, m_polygons[poly_index][i], true);
		}
	}
}

unsigned int World::polygons()
{
	return m_polygons.size();
}

Vector3<unsigned int> World::get_color(unsigned int index) const
{
	return m_colors[index - 1];
}

