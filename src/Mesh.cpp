#include "Mesh.hpp"

Mesh::Mesh()
{ }

Mesh::Mesh(Mesh& m) :
	m_triangles(m.m_triangles),
	m_verts(m.m_verts),
	m_norms(m.m_norms)
{ }

Mesh::Mesh(const Mesh& m) :
	m_triangles(m.m_triangles),
	m_verts(m.m_verts),
	m_norms(m.m_norms)
{ }

Mesh::Mesh(const std::vector<Triangle>& tris)
{
	for (auto t = tris.begin(); t != tris.end(); t++) AddFace(*t);
}

Mesh::Mesh(const std::list<Triangle>& tris)
{
	for (auto t = tris.begin(); t != tris.end(); t++) AddFace(*t);
}

void Mesh::operator=(const Mesh& m)
{
	m_triangles = m.m_triangles;
	m_verts = m.m_verts;
	m_norms = m.m_norms;
}

Mesh::Triangle Mesh::operator[](unsigned int index)
{
	// Constant Time
	// Maybe should check that index is within bounds?
	Triangle t;
	t.p[0] = m_verts[m_triangles[index].p[0]];
	t.p[1] = m_verts[m_triangles[index].p[1]];
	t.p[2] = m_verts[m_triangles[index].p[2]];
	t.n[0] = m_norms[m_triangles[index].n[0]];
	t.n[1] = m_norms[m_triangles[index].n[1]];
	t.n[2] = m_norms[m_triangles[index].n[2]];
	return t;
}
Mesh::Triangle Mesh::Get(unsigned int index)
{
	// Constant Time
	// Maybe should check that index is within bounds?
	Triangle t;
	t.p[0] = m_verts[m_triangles[index].p[0]];
	t.p[1] = m_verts[m_triangles[index].p[1]];
	t.p[2] = m_verts[m_triangles[index].p[2]];
	t.n[0] = m_norms[m_triangles[index].n[0]];
	t.n[1] = m_norms[m_triangles[index].n[1]];
	t.n[2] = m_norms[m_triangles[index].n[2]];
	return t;
}
void Mesh::AddFace(const Mesh::Triangle& t)
{
	// Same as AddFace
	AddFace(t.p[0], t.p[1], t.p[2], t.n[0], t.n[1], t.n[2]);
}

void Mesh::AddFace(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
		const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3)
{
	// O(n)
	// n = |verts| + |norms|
	if (v1 == v2) return;
	if (v2 == v3) return;
	if (v1 == v3) return;
	Index_Triangle t;
	find_verts(v1, v2, v3, t.p[0], t.p[1], t.p[2]); //Linear
	find_norms(n1, n2, n3, t.n[0], t.n[1], t.n[2]); //Linear
	m_triangles.push_back(t); // Constant
}

unsigned int Mesh::normals() const
{
	// Constant time
	return m_norms.size();
}

unsigned int Mesh::vertices() const
{
	// Constant time
	return m_verts.size();
}

const std::vector<glm::vec3>& Mesh::get_normals() const
{
	// Constant time
	return m_verts;
}

const std::vector<glm::vec3>& Mesh::get_vertices() const
{
	// Constant time
	return m_norms;
}

const std::vector<Mesh::Triangle> Mesh::get_triangles() const
{
	// O(n)
	// For each index triangle, get the desired things
	std::vector<Triangle> triangles;
	for (auto face = m_triangles.begin(); face != m_triangles.end(); face++)
	{
		Triangle t;
		t.p[0] = m_verts[(*face).p[0]];
		t.p[1] = m_verts[(*face).p[1]];
		t.p[2] = m_verts[(*face).p[2]];
		t.n[0] = m_norms[(*face).n[0]];
		t.n[1] = m_norms[(*face).n[1]];
		t.n[2] = m_norms[(*face).n[2]];
		triangles.push_back(t);
	}
	return triangles;
}

void Mesh::Export(const std::string& fname)
{
	std::filebuf fb;
	fb.open(fname.c_str(), std::ios::out);
	std::ostream os(&fb);
	std::string comment = "# 3D Polygonized Mesh\n"
		"# Program Written by Evan Wilde\n";
#ifdef DEBUG
	std::cerr << "Exporting Mesh...\n";
#endif
	os << comment;
	os << "\n# Vertices\n";
	for (unsigned int i = 0; i < m_verts.size(); i++)
	{
		os << "v "
			<< m_verts[i].x << ' '
			<< m_verts[i].y << ' '
			<< m_verts[i].z << '\n';
	}
	os << "\n# Normals\n";
	for (unsigned int i = 0; i < m_norms.size(); i++)
	{
		os << "vn "
			<< m_norms[i].x<< ' '
			<< m_norms[i].y<< ' '
			<< m_norms[i].z<< '\n';
	}
	os << "\n# Faces\n";
	for (auto face = m_triangles.begin(); face != m_triangles.end(); face++)
	{
		os << "f "
			<< (*face).p[0] << "//" << (*face).n[0] << ' '
			<< (*face).p[1] << "//" << (*face).n[1] << ' '
			<< (*face).p[2] << "//" << (*face).n[2] << '\n';
	}

	os << "# " << m_verts.size() << " Vertices Written\n";
	os << "# " << m_norms.size() << " Normals Written\n";
	os << "# " << m_triangles.size() << " Triangles Written\n";
#ifdef DEBUG
	std::cerr << "Mesh Exported\n";
#endif
}

void Mesh::Import(const std::string& fname)
{
	//TODO: allow a user to select which object to use from a file
	//TODO: Cleanup vertices on import
	//TODO: Only insert verts, normals, and faces on good file
	// I'm including uv index for future support, but
	// it won't be useful for now
	std::string line;
	std::vector<unsigned int> vertex_index, uv_index, normal_index;
	std::vector<unsigned int> tris_to_fix; // Which triangles need normals
	std::ifstream in_file(fname.c_str());
	if (!in_file.is_open())
	{
		std::cerr << "Failed to open " << fname << '\n';
		return;
	}
	// Only handles a single object since this goes to one mesh
#ifdef DEBUG
	std::cout << "Importing " << fname << '\n';
#endif

	while (getline(in_file, line))
	{
		// Comment
		if (line.c_str()[0] == '#') continue;
		// Object
		else if(line.c_str()[0] == 'o' && line.c_str()[1] == ' ')
			break; // We only do one object
		// Vertex
		else if(line.c_str()[0] == 'v' && line.c_str()[1] == ' ')
		{
			float tmpx, tmpy, tmpz;
			sscanf(line.c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			m_verts.push_back(glm::vec3(tmpx, tmpy, tmpz));
		}
		// Vertex Normal
		else if (line.c_str()[0] == 'v' && line.c_str()[1] == 'n' &&
					line.c_str()[2] == ' ')
		{
			float tmpx, tmpy, tmpz;
			sscanf(line.c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			m_norms.push_back(glm::vec3(tmpx, tmpy, tmpz));
		}
		// Face
		else if (line.c_str()[0] == 'f' && line.c_str()[1] == ' ')
		{
			Index_Triangle t;
			unsigned int tris_number = m_triangles.size();
			std::string s = line;
#ifdef DEBUG
			std::cout << line  << '\n';
#endif
			std::string pattern = "f ([0-9]*)(?:/([0-9]*)?/([0-9]*)?)? ([0-9]*)(?:/([0-9]*)?/([0-9]*)?)? ([0-9]*)(?:/([0-9]*)?/([0-9]*)?)?";
			std::vector<std::string> matches;
			std::smatch match;
			std::regex face_re(pattern);
			while(std::regex_search(s, match,face_re))
			{
				for (auto x : match) matches.push_back(x);
				s = match.suffix().str();
			}
			// Check quality of input
			if (matches[1].compare("") == 0 ||
					matches[4].compare("") == 0 ||
					matches[7].compare("") == 0)
			{
				in_file.close();
				std::cerr << "Malformed File: " << fname << '\n';
				return;
			}

			// Build Triangle?
			t.p[0] = std::stof(matches[1]);
			t.p[1] = std::stof(matches[4]);
			t.p[2] = std::stof(matches[7]);

#ifdef DEBUG
			std::cout << "Normal: " << matches[3] << ", " <<
				matches[6] << ", " << matches[9] << '\n';
#endif

			// If any normals are missing, the face is bad
			//tris_to_fix.push_back(tris_number);
			if (matches[3].compare("") == 0 ||
				matches[6].compare("") == 0 ||
				matches[9].compare("") == 0)
			{
				tris_to_fix.push_back(tris_number);
			}
			else
			{
				t.n[0] = std::stof(matches[3]);
				t.n[1] = std::stof(matches[6]);
				t.n[2] = std::stof(matches[9]);
			}
			m_triangles.push_back(t);
		}
	}
	fix_norms(tris_to_fix);
	in_file.close();

#ifdef DEBUG
	std::cout << "Finished importing File\n";
#endif
}

void Mesh::Draw()
{
	for (auto face = m_triangles.begin(); face != m_triangles.end(); face++)
		draw_Triangle((*face));
}

#ifdef DEBUG
void Mesh::Details()
{
	std::cout << "Vertices: " << m_verts.size() << '\n'
		<< "Normals: " << m_norms.size() << '\n'
		<< "Triangles: " << m_triangles.size() << '\n';
	std::cout << "First Vertex: " << m_verts[0].x << " " << m_verts[0].y << " " << m_verts[0].z  << '\n';
	std::cout << "First Triangle Vertex Index: " << m_triangles[0].p[0] << '\n';
}
#endif

/*
 * Protected Methods
 */

void Mesh::find_verts(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
		unsigned int& i1, unsigned int& i2, unsigned int& i3)
{
	bool v1_found = false;
	bool v2_found = false;
	bool v3_found = false;

	for (unsigned int index = 0; index < m_verts.size(); index++)
	{
		if (!v1_found && v1 == m_verts[index])
		{
			i1 = index + 1;
			v1_found = true;
		}

		if (!v2_found && v2 == m_verts[index])
		{
			i2 = index + 1;
			v2_found = true;
		}

		if (!v3_found && v3 == m_verts[index])
		{
			i3 = index + 1;
			v3_found = true;
		}
	}

	if (!v1_found)
	{
		m_verts.push_back(v1);
		i1 = m_verts.size();
	}

	if (!v2_found)
	{
		m_verts.push_back(v2);
		i2 = m_verts.size();
	}

	if (!v3_found)
	{
		m_verts.push_back(v3);
		i3 = m_verts.size();
	}

}

void Mesh::find_norms(const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3,
		unsigned int& i1, unsigned int& i2, unsigned int& i3)
{
	bool n1_found = false;
	bool n2_found = false;
	bool n3_found = false;

	for (unsigned int index = 0; index < m_norms.size(); index++)
	{
		if (!n1_found && n1 == m_norms[index])
		{
			i1 = index + 1;
			n1_found = true;
		}

		if (!n2_found && n2 == m_norms[index])
		{
			i2 = index + 1;
			n2_found = true;
		}

		if (!n3_found && n3 == m_norms[index])
		{
			i3 = index + 1;
			n3_found = true;
		}
	}

	if (!n1_found)
	{
		m_norms.push_back(n1);
		i1 = m_norms.size();
	}

	if (!n2_found)
	{
		m_norms.push_back(n2);
		i2 = m_norms.size();
	}

	if (!n3_found)
	{
		m_norms.push_back(n3);
		i3 = m_norms.size();
	}
}

void Mesh::fix_norms(std::vector<unsigned int>& tris)
{
#ifdef DEBUG
	std::cout << "Faces to fix: " << tris.size() << '\n';
#endif
	for(auto t = tris.begin(); t != tris.end(); t++)
	{
		Index_Triangle& it = m_triangles[(*t)];
		const glm::vec3 p1 = m_verts[it.p[0] - 1];
		const glm::vec3 p2 = m_verts[it.p[1] - 1];
		const glm::vec3 p3 = m_verts[it.p[2] - 1];
		const glm::vec3 v = p2 - p1;
		const glm::vec3 w = p3 - p1;
		m_norms.push_back(glm::cross(v, w));
		it.n[0] = it.n[1] = it.n[2] = m_norms.size();
	}


	/*
#ifdef DEBUG
	unsigned int fixed_faces = 0;
#endif
	for (auto face = m_triangles.begin(); face != m_triangles.end(); face++)
	{
		if ((*face).n[0] == 0 || (*face).n[1] == 0 || (*face).n[2] == 0)
		{
#ifdef DEBUG
			fixed_faces += 1;
#endif
			const glm::vec3 p1 = m_verts[(*face).p[0]];
			const glm::vec3 p2 = m_verts[(*face).p[1]];
			const glm::vec3 p3 = m_verts[(*face).p[2]];

			const glm::vec3 v = p2 - p1;
			const glm::vec3 w = p3 - p1;
			m_norms.push_back(glm::cross(v, w));
			(*face).n[0] = (*face).n[1] = (*face).n[2] = m_norms.size();
		}
	}
#ifdef DEBUG
	std::cout << "Faces Fixed: " << fixed_faces << '\n';
#endif
*/
}

/*
 * Private Methods
 */

void Mesh::draw_Triangle(const Index_Triangle& t)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3f(m_norms[t.n[0] - 1].x, m_norms[t.n[0] - 1].y, m_norms[t.n[0] - 1].z);
	glVertex3f(m_verts[t.p[0] - 1].x, m_verts[t.p[0] - 1].y, m_verts[t.p[0] - 1].z);
	glNormal3f(m_norms[t.n[1] - 1].x, m_norms[t.n[1] - 1].y, m_norms[t.n[1] - 1].z);
	glVertex3f(m_verts[t.p[1] - 1].x, m_verts[t.p[1] - 1].y, m_verts[t.p[1] - 1].z);
	glNormal3f(m_norms[t.n[2] - 1].x, m_norms[t.n[2] - 1].y, m_norms[t.n[2] - 1].z);
	glVertex3f(m_verts[t.p[2] - 1].x, m_verts[t.p[2] - 1].y, m_verts[t.p[2] - 1].z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(m_norms[t.n[0] - 1].x, m_norms[t.n[0] - 1].y, m_norms[t.n[0] - 1].z);
	glVertex3f(m_verts[t.p[0] - 1].x, m_verts[t.p[0] - 1].y, m_verts[t.p[0] - 1].z);
	glNormal3f(m_norms[t.n[1] - 1].x, m_norms[t.n[1] - 1].y, m_norms[t.n[1] - 1].z);
	glVertex3f(m_verts[t.p[1] - 1].x, m_verts[t.p[1] - 1].y, m_verts[t.p[1] - 1].z);
	glNormal3f(m_norms[t.n[2] - 1].x, m_norms[t.n[2] - 1].y, m_norms[t.n[2] - 1].z);
	glVertex3f(m_verts[t.p[2] - 1].x, m_verts[t.p[2] - 1].y, m_verts[t.p[2] - 1].z);
	glNormal3f(m_norms[t.n[0] - 1].x, m_norms[t.n[0] - 1].y, m_norms[t.n[0] - 1].z);
	glVertex3f(m_verts[t.p[0] - 1].x, m_verts[t.p[0] - 1].y, m_verts[t.p[0] - 1].z);
	glEnd();
}


