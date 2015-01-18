#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "polygon.h"

class World
{
	public:
		void add_polygon(Polygon p);
	private:
		std::list<Polygon> m_polygons;
		std::list<Vector3<float>> m_colors;


};

#endif //WORLD_H
