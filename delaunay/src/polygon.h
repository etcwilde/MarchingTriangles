#ifndef POLYGON_H
#define POLYGON_H

#define PNTS_MAX 300
#define PNTS_RAD 8

#include <vector>
#include <iostream>

#include <string.h>

#include "vector.h"

// TODO: extract color from vertex

class Polygon
{
	public:
		Polygon();
		~Polygon();

		void add_point(Vector2<int> pt, unsigned int color_index=1);
		void add_point(int x, int y, unsigned int color_index=1);

		unsigned int size();

		Vector2<int> operator[](const int index);

		unsigned int color(unsigned int index);

		friend std::ostream& operator<<(std::ostream& os,
				const Polygon& p)
		{
			os << '\n';
			os << "Vertices: " << p.m_points.size();
			for (register unsigned int v = 0; 
					v < p.m_points.size(); ++v)
			{
				os << ' ' << p.m_points[v];
			}
			os << '\n';
			os << "Colors: " << p.m_colors.size();
			for (register unsigned int c = 0; 
					c < p.m_colors.size(); ++c)
			{
				os << ' ' << p.m_colors[c];
			}
		}

	private:
		std::vector<Vector2<int>> m_points;
		std::vector<unsigned int> m_colors;
};


#endif // POLYGON_H
