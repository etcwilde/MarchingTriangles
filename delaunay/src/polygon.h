#ifndef POLYGON_H
#define POLYGON_H

#define PNTS_MAX 300
#define PNTS_RAD 8

#include <vector>

#include <string.h>

#include "vector.h"

class Polygon
{
	public:
		Polygon();
		~Polygon();

		void add_point(Vector2<int> pt, unsigned int color_index=1);
		void add_point(int x, int y, unsigned int color_index=1);

		unsigned int size();

	private:
		std::vector<Vector2<int>> m_points;
		std::vector<unsigned int> m_colors;
};


#endif // POLYGON_H
