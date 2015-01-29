#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <list>
#include <vector>

#include <glfw-cxx/glfw-cxx.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string.h>

#include "polygon.h"

#include "drawlib.h"

#define DEL_EPS 0.000001

class World
{
	public:
		World();

		void add_polygon(Polygon p);
		void add_color(Vector3<unsigned int> color);
		void set_colors(std::vector<Vector3<unsigned int>> colors);
		void set_polygons(std::vector<Polygon> polygons);

		void draw();

		unsigned int polygons();

		void Triangulate();
		void ClearTriangles();

		void ToggleWireframe();
		void ToggleLines();
		void ToggleVerts();

		friend std::ostream& operator << (std::ostream& os,
				const World& w)
		{
			os << "Colors: " << w.m_colors.size();
			for (unsigned int c = 0; c < w.m_colors.size(); ++c)
			{
				os << ' ' << w.get_color(c+1);
			}
			os << '\n';
			os << "Polygons: " << w.m_polygons.size();
			for (unsigned int p = 0; p < w.m_polygons.size(); ++p)
			{
				os << ' ' << w.m_polygons[p];
			}

			return os;
		}



	private:

		void draw_points();
		void draw_outline();
		void draw_triangles();

		void triangulate();

		bool circum_circle_intersect(Vector2<int> test_point, 
				Vector2<int> p1, Vector2<int> p2, 
				Vector2<int> p3, Vector2<int>& centre_point, 
				float& r);




		Vector3<unsigned int> get_color(unsigned int index) const;
		std::vector<Vector3<unsigned int>> m_colors;
		std::vector<Polygon> m_polygons;
		std::vector<Triangle> m_triangles;

		bool m_wireframe;
		bool m_lines;
		bool m_verts;
};

#endif //WORLD_H
