#include "fileloader.h"

bool FileLoader::LoadPolygons(World& world,
		const std::string&  obj_filename)
{
	string line;
	ifstream in_file(obj_filename);

	if (!in_file.is_open())
	{
		cerr << "Failed to open: " << obj_filename << '\n';
		return false;
	}
	in_file.close();
	return true;

}
