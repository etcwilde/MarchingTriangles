#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <list>
#include <vector>

#include <glfw-cxx/glfw-cxx.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

#include "polygon.h"

#include "drawlib.h"

class World
{
	public:
		void add_polygon(Polygon p);
		void add_color(Vector3<unsigned int> color);
		void set_colors(std::vector<Vector3<unsigned int>> colors);
		void set_polygons(std::vector<Polygon> polygons);

		void draw();

		unsigned int polygons();

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
		Vector3<unsigned int> get_color(unsigned int index) const;
		std::vector<Vector3<unsigned int>> m_colors;
		std::vector<Polygon> m_polygons;
};

#endif //WORLD_H
