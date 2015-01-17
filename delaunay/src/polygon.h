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

		bool add_point(Vector2<int> pt);
		bool add_point(int x, int y);

		unsigned int size();

	private:
		unsigned int m_count;
};


#endif // POLYGON_H
