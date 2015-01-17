#include "polygon.h"

Polygon::Polygon()
{
	memset(m_points, 0, sizeof(m_points));
	m_count = 0;
}


Polygon::~Polygon() {}


