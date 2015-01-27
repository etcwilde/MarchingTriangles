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
	draw_outline();
	draw_points();
	draw_triangles();
}

unsigned int World::polygons()
{
	return m_polygons.size();
}

void World::Triangulate()
{
	triangulate();
}

void World::ClearTriangles()
{
	m_triangles.clear();
}

Vector3<unsigned int> World::get_color(unsigned int index) const
{
	return m_colors[index - 1];
}

void World::draw_points()
{
	unsigned int poly_index;
	for (poly_index = 0; poly_index < m_polygons.size(); ++poly_index)
		for (unsigned int i = 0; i < m_polygons[poly_index].size();
				++i)
		{
			unsigned int color = m_polygons[poly_index].color(i);
			Vector3<unsigned int> color_v = m_colors[color];
			glColor3ub(color_v.x, color_v.y, color_v.z);
			DrawLib::drawCircle(5, m_polygons[poly_index][i], true);
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

void World::draw_triangles()
{
	for (unsigned int t = 0; t < m_triangles.size(); ++t)
	{
		// Grab the triangle data
		glBegin(GL_TRIANGLES);
		{
			Vector3<unsigned int> color1 =
				m_colors[m_triangles[t].color(0)];
			Vector3<unsigned int> color2 =
				m_colors[m_triangles[t].color(1)];
			Vector3<unsigned int> color3 =
				m_colors[m_triangles[t].color(2)];

			glColor3ub(color1.x, color1.y, color1.z);
			glVertex2i(m_triangles[t][0].x, m_triangles[t][0].y);
			glColor3ub(color2.x, color2.y, color2.z);
			glVertex2i(m_triangles[t][1].x, m_triangles[t][1].y);
			glColor3ub(color3.x, color3.y, color3.z);
			glVertex2i(m_triangles[t][2].x, m_triangles[t][2].y);
		}
		glEnd();
	}
}

void World::triangulate()
{
	bool pt_inside;
	int x_min, x_max, y_min, y_max, x_center, y_center;
	int dx, dy, dmax;
	// Nothing to process
	if (m_polygons.size() == 0) return;

	// Process each polygon
	for (unsigned int p = 0; p < m_polygons.size(); ++p)
	{
		// Do we have enough triangles?
		if (m_polygons[p].size() < 3) continue;

		// We have enough triangles.
		x_min = x_max = m_polygons[p][0].x;
		y_min = y_max = m_polygons[p][0].y;

		for (unsigned int v = 0; v < m_polygons[p].size(); ++v)
		{
			x_min = x_min > m_polygons[p][v].x ? m_polygons[p][v].x : x_min;
			x_max = x_max < m_polygons[p][v].x ? m_polygons[p][v].x : x_max;
			y_min = y_min > m_polygons[p][v].y ? m_polygons[p][v].y : y_min;
			y_max = y_max < m_polygons[p][v].y ? m_polygons[p][v].y : y_max;
		}
		x_max += 1; y_max += 1;

		std::cerr
			<< "Min: " << '(' << x_min << ", " << y_min << ')' << ' '
			<< "Max: " << '(' << x_max << ", " << y_max << ')' << '\n';

		dx = x_max - x_min;
		dy = y_max - y_min;
		dmax = dx > dy ? dx : dy;

		// Draw bounding box
		Triangle t1(Vector2<int>(x_max, y_max),
				Vector2<int>(x_min, y_max),
				Vector2<int>(x_min,y_min),
				0, 2, 1);

		Triangle t2(Vector2<int>(x_min, y_min),
				Vector2<int>(x_max, y_min),
				Vector2<int>(x_max,y_max),
				1, 2, 0);

		m_triangles.push_back(t1);
		m_triangles.push_back(t2);
	}
}

