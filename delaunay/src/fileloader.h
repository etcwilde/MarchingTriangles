#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <stdlib.h>

#include "polygon.h"
#include "vector.h"
#include "world.h"

using namespace std;

class FileLoader
{
	public:
		bool LoadPolygons(World* world,
				const std::string& obj_filename);

	private:
		std::vector<Polygon> m_polygons;
		std::vector<Vector3<unsigned int>> m_colors;

};

#endif //LOADER_H
