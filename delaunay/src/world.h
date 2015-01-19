#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <vector>

#include "polygon.h"

class World
{
	public:
		void add_polygon(Polygon p);
		void set_colors(std::vector<Vector3<unsigned int>> colors);
		void set_polygons(std::vector<Vector3<unsigned int>> poly);

	private:
		std::vector<Vector3<unsigned int>> m_colors;
		std::vector<Polygon> m_polygons;

};

#endif //WORLD_H
