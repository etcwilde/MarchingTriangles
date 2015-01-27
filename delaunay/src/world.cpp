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

	/*draw_outline(); */
	unsigned int poly_index;
	/**/

	draw_outline();
	draw_points();
}

unsigned int World::polygons()
{
	return m_polygons.size();
}

Vector3<unsigned int> World::get_color(unsigned int index) const
{
	return m_colors[index - 1];
}

void World::draw_points()
{
	unsigned int poly_index;
	for (poly_index = 0; poly_index < m_polygons.size(); ++poly_index)
	{
		// First edge

		/*
		const Polygon &current_polygon = m_polygons[poly_index];
		glBegin(GL_LINES);
		{
		Vector3<unsigned int> color_v =
			m_colors[
				current_polygon.color(
					current_polygon.size() - 1
				)
			];
		glColor3ub(color_v.x, color_v.y, color_v.z);
		glVertex2i(current_polygon[current_polygon.size() - 1].x
				current_polygon[current_polygon.size() -1].y);

		color_v = m_colors[current_polygon.color(0)];
		glColor3ub(color_v.x, color_v.y, color_v.z);
		glVertex2i(current_polygon[0].x, current_polygon[0].y);
		}
		glEnd();
		*/

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

void World::draw_outline()
{
	unsigned int poly_index;
	for (poly_index = 0; poly_index < m_polygons.size(); ++poly_index)
	{
		Polygon &current_polygon = m_polygons[poly_index];

		if (current_polygon.size() < 2) continue;
		glBegin(GL_LINES);
		{
			Vector3<unsigned int> color_v=
				m_colors[
				current_polygon.color(current_polygon.size()-1)
				];
			glColor3ub(color_v.x, color_v.y, color_v.z);
			glVertex2i(
					current_polygon[current_polygon.size()-1].x,
					current_polygon[current_polygon.size()-1].y
				  );

			color_v = m_colors[ current_polygon.color(0)];
			glColor3ub(color_v.x, color_v.y, color_v.z);
			glVertex2i( current_polygon[0].x,
					current_polygon[0].y);
		}
		glEnd();

		for (unsigned int i = 0; i < current_polygon.size() -1; ++i)
		{
			glBegin(GL_LINES);
			{
				Vector3<unsigned int> color1 =
					m_colors[current_polygon.color(i)];
				Vector3<unsigned int> color2 =
					m_colors[current_polygon.color(i+1)];
				glColor3ub(color1.x, color1.y, color1.z);
				glVertex2i(current_polygon[i].x,
						current_polygon[i].y);
				glColor3ub(color2.x, color2.y, color2.z);
				glVertex2i(current_polygon[i+1].x,
						current_polygon[i+1].y);
			}
			glEnd();
		}
	}
}

