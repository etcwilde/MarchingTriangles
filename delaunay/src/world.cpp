#include "world.h"

World::World()
	: m_wireframe(false),
	m_lines(false),
	m_verts(true)

{
}
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
	if (m_lines) draw_outline();
	if (m_verts) draw_points();
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


void World::ToggleWireframe()
{
	m_wireframe = !m_wireframe;
}

void World::ToggleLines()
{
	m_lines = !m_lines;
}

void World::ToggleVerts()
{
	m_verts = !m_verts;
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
		Vector3<unsigned int> color1 =
			m_colors[m_triangles[t].color(0)];
		Vector3<unsigned int> color2 =
			m_colors[m_triangles[t].color(1)];
		Vector3<unsigned int> color3 =
			m_colors[m_triangles[t].color(2)];

		if(m_wireframe)
		{
			glBegin(GL_LINES);
			glColor3ub(color1.x, color1.y, color1.z);
			glVertex2i(m_triangles[t][0].x, m_triangles[t][0].y);
			glColor3ub(color2.x, color2.y, color2.z);
			glVertex2i(m_triangles[t][1].x, m_triangles[t][1].y);
			glVertex2i(m_triangles[t][1].x, m_triangles[t][1].y);
			glColor3ub(color3.x, color3.y, color3.z);
			glVertex2i(m_triangles[t][2].x, m_triangles[t][2].y);
			glVertex2i(m_triangles[t][2].x, m_triangles[t][2].y);
			glColor3ub(color1.x, color1.y, color1.z);
			glVertex2i(m_triangles[t][0].x, m_triangles[t][0].y);
		}
		else
		{
			glBegin(GL_TRIANGLES);
			glColor3ub(color1.x, color1.y, color1.z);
			glVertex2i(m_triangles[t][0].x, m_triangles[t][0].y);
			glColor3ub(color2.x, color2.y, color2.z);
			glVertex2i(m_triangles[t][1].x, m_triangles[t][1].y);
			glColor3ub(color3.x, color3.y, color3.z);
			glVertex2i(m_triangles[t][2].x, m_triangles[t][2].y);
		}
		glEnd();
	}

	// Generate Vertex buffers
	// TODO -- Use vertex buffers to decrease GPU calls

	//unsigned int total_verts = m_triangles.size() * 3;

	/*for (unsigned int t = 0; t < m_triangles.size(); ++t)
	{
	} */


	//std::cerr << "Vertices: " << total_verts << '\n';
}

void World::triangulate()
{
	std::vector<Vector2<int>> bisectors;
	// Nothing to process
	if (m_polygons.size() == 0) return;

	// Process each polygon
	for (unsigned int p = 0; p < m_polygons.size(); ++p)
	{
		// Are there enough verts for a triangle?
		if (m_polygons[p].size() < 3) continue;

		if (m_polygons[p].size() == 3)
		{
			// One triangulation
			Triangle T(m_polygons[p][0], m_polygons[p][1],
					m_polygons[p][2],
					m_polygons[p].color(0),
					m_polygons[p].color(1),
					m_polygons[p].color(2));
			m_triangles.push_back(T);

			continue;
		}

		// Okay, for each vertex in the polygon, we need to check if
		// any of the others are within the circum-circle
		//
		// If not, then add the triangle to the m_triangles

		Vector2<int> centre;
		float rad;

		// Naive way
		for (unsigned int v = 0; v < m_polygons[p].size(); ++v)
			for (unsigned int v2 = v + 1; v2 < m_polygons[p].size(); ++v2)
				for (unsigned int v3 = v2 + 1; v3 < m_polygons[p].size(); ++v3)
				{
					bool good_triangulation = true;
					for(unsigned int test_v = 0;
							test_v < m_polygons[p].size(); ++test_v)
					{
						if (test_v == v || test_v == v2
								|| test_v == v3
						   ) continue;
						if (circum_circle_intersect
							(m_polygons[p][test_v],
							m_polygons[p][v],
							m_polygons[p][v2],
							m_polygons[p][v3],
							centre, rad))
						{
							good_triangulation = false;
							break;
						}
					}
					if (good_triangulation)
					{
					Triangle T
					(m_polygons[p][v], m_polygons[p][v2],
					 m_polygons[p][v3],
					 m_polygons[p].color(v),
					 m_polygons[p].color(v2),
					 m_polygons[p].color(v3));
					m_triangles.push_back(T);
					}
					else continue;
				}
	}
}

bool World::circum_circle_intersect(Vector2<int> test_point, Vector2<int> p1,
		Vector2<int> p2, Vector2<int> p3,
		Vector2<int>& centre_point, float& r)
{
	float m1, m2, mx1, mx2, my1, my2;
	float dx, dy, rsqr, drsqr;

	if (abs(p1.y - p2.y) < DEL_EPS && abs(p2.y - p3.y) < DEL_EPS)
		return false;

	if (abs(p2.y - p1.y) < DEL_EPS)
	{
		m2 = - (p3.x - p2.x) / (p3.y - p2.y);
		mx2 = (p2.x + p3.x) / 2.0;
		my2 = (p2.y + p3.y) / 2.0;
		// Centre point
		centre_point.x = (int)(p2.x + p1.x) / 2.0;
		centre_point.y = (int)m2 * (centre_point.x - mx2) + my2;
	}
	else if(abs(p3.y - p2.y) < DEL_EPS)
	{
		m1 = -(p2.x - p1.x) / (p2.y - p1.y);
		mx1 = (p1.x + p2.x) / 2.0;
		my1 = (p1.y + p2.y) / 2.0;
		centre_point.x = (int)(p3.x + p2.x) / 2.0;
		centre_point.y = (int) m1 * (centre_point.x - mx1) + my1;
	}
	else
	{
		m1 = -(p2.x - p1.x) / (p2.y - p1.y);
		m2 = -(p3.x - p2.x) / (p3.y - p2.y);
		mx1 = (p1.x + p2.x) / 2.0;
		mx2 = (p2.x + p3.x) / 2.0;
		my1 = (p1.y + p2.y) / 2.0;
		my2 = (p2.y + p3.y) / 2.0;
		centre_point.x = (int)(m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
		centre_point.y = (int)m1 * (centre_point.x - mx1) + my1;
	}

	dx = p2.x - centre_point.x;
	dy = p2.y - centre_point.y;
	rsqr = dx * dx + dy * dy;
	r = sqrt(rsqr);
	dx = test_point.x - centre_point.x;
	dy = test_point.y - centre_point.y;
	drsqr = dx * dx + dy * dy;
	/*std::cerr << "Centre to p2: " << rsqr << '\t'
		<< "Centre to test point: " << drsqr << '\n'; */
	return (drsqr <= rsqr);
}
