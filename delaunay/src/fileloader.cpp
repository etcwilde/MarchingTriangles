#include "fileloader.h"

bool FileLoader::LoadPolygons(World& world,
		const std::string&  obj_filename)
{
	string line;
	ifstream in_file(obj_filename);
	vector<unsigned int> color_index;

	if (!in_file.is_open())
	{
		cerr << "Failed to open: " << obj_filename << '\n';
		return false;
	}

	bool poly_set = false;
	bool color_set = false;
	Polygon current_polygon;
	while (getline(in_file, line))
	{
		// Comment
		if (line.c_str()[0] == '#') continue;
		// Newline
		else if (line.c_str()[0] == '\n') continue;
		// Polygon
		else if (line.c_str()[0] == 'p' && line.c_str()[1] == ' ')
		{
			cerr << "Polygon!\n";
			if (poly_set) m_polygons.push_back(current_polygon);
			current_polygon = Polygon();
			color_set = false;
		}
		else if (line.c_str()[0] == 'c' && line.c_str()[1] == ' ')
		{
			cerr << "Vertex Color\n";


		}
		else if (line.c_str()[0] == 'v' && line.c_str()[1] == ' ')
		{
			cerr << "Vertex\n";
		}
	}

	in_file.close();
	return true;
}
