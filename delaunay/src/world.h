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

	private:
		Vector3<unsigned int> get_color(unsigned int index);
		std::vector<Vector3<unsigned int>> m_colors;
		std::vector<Polygon> m_polygons;
};

#endif //WORLD_H
