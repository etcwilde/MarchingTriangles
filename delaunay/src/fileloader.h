#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>
#include <vector>

#include "polygon.h"
#include "vector.h"
#include "world.h"

using namespace std;

class FileLoader
{
	public:
		bool LoadPolygons(World& world,
				const std::string& obj_filename);

	private:
		std::vector<Vector3<int>> m_colors;
		std::vector<Vector2<int>> m_vertices;
};

#endif //LOADER_H
