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
	Polygon current_poly;
	while (getline(in_file, line))
	{
		// Comment
		if (line.c_str()[0] == '#') continue;

		// Newline
		else if (line.c_str()[0] == '\n') continue;

		// Color
		else if (line.c_str()[0] == 'c' && line.c_str()[1] == ' ')
		{
			unsigned int tmpr, tmpg, tmpb;
			sscanf(line.c_str(), "c %u %u %u", &tmpr, &tmpg, &tmpb);
			cerr << "Color " << tmpr << ' ' << tmpg << ' ' <<
				tmpb << '\n';

			tmpr = tmpr > 255 ? 255 : tmpr;
			tmpg = tmpg > 255 ? 255 : tmpg;
			tmpb = tmpb > 255 ? 255 : tmpb;

			m_colors.push_back(Vector3<unsigned int>(tmpr,
						tmpg, tmpb));
		}

		// Polygon
		else if (line.c_str()[0] == 'p' && line.c_str()[1] == ' ')
		{
			if (poly_set) m_polygons.push_back(current_poly);
			current_poly = Polygon();
			poly_set = true;
			cerr << "Polygon!\n";
		}

		// Vertex
		else if (line.c_str()[0] == 'v' && line.c_str()[1] == ' ')
		{
			poly_set = true;
			cerr << "Vertex!\n";
			cerr << line << '\n';

			std::string s = line;
			std::string pattern = "v ([0-9]*) ([0-9]*)(?: ([0-9]*))?";
			std::vector<std::string> matches;
			std::smatch match;
			std::regex re(pattern);
			while (std::regex_search(s, match, re))
			{
				for (auto x : match) matches.push_back(x);
				s = match.suffix().str();
			}
			if (matches[3].compare("") == 0) matches[3] = "1";
			for (unsigned int i = 0; i < matches.size(); ++i)
			{
				cerr << i << ": " << matches[i] << '\n';
			}
			Vector2<int> pt(strtoul(matches[0].c_str(), NULL, 0),
					strtoul(matches[1].c_str(), NULL, 0));


			current_poly.add_point(pt, strtoul(matches[2].c_str(),
						NULL, 0) - 1);
		}

	}
	if (poly_set)
	{
		m_polygons.push_back(current_poly);
	}
	in_file.close();

	if (m_colors.size() == 0)
	{
		m_colors.push_back(Vector3<unsigned int>(255, 255, 255));
	}
	cerr << "Colors: " << m_colors.size() << '\n';
	for (unsigned int i = 0; i < m_colors.size(); ++i)
		cerr << m_colors[i].x << ' ' <<
			m_colors[i].y << ' ' << m_colors[i].z << '\n';

	cerr << "Polygons: " << m_polygons.size() << '\n';
	/*for (unsigned int i = 0; i < m_polygons.size(); ++i)
	{
	} */
	return true;
}
