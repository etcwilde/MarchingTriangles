#ifndef POLYGON_H
#define POLYGON_H

#define PNTS_MAX 300
#define PNTS_RAD 8

#include "vector.h"
#include <string.h>

class Polygon
{
	public:
		Polygon();
		~Polygon();

		bool add_point(Vector2<int> pt);
		bool add_point(int x, int y);

		unsigned int size();

	private:
		Vector2<int> m_points[PNTS_MAX];
		unsigned int m_count;
};


#endif // POLYGON_H
