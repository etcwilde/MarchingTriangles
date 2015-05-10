#include "PolyTris.hpp"
// Protected Methods

Mesh TrisPoly::polygonize()
{
	seedHexagon(m_scene.GetCenterVertex());

	Mesh m;
	for (unsigned int i = 0; i < m_container.m_faces.size(); i++)
	{
		m.AddFace(m_container.m_vertices[m_container.m_faces[i].vert_index[0]],
			m_container.m_vertices[m_container.m_faces[i].vert_index[1]],
			m_container.m_vertices[m_container.m_faces[i].vert_index[2]],
			m_container.m_normals[m_container.m_faces[i].vert_index[0]],
			m_container.m_normals[m_container.m_faces[i].vert_index[1]],
			m_container.m_normals[m_container.m_faces[i].vert_index[2]]);
	}
	return m;
}

// Private Methods
// Given a seed, generates a seed hexagon
void TrisPoly::seedHexagon(const glm::vec3& start)
{
	const glm::vec3 seed = m_scene.Project(start);

	const glm::vec3 n = m_scene.Normal(seed);
	glm::vec3 t, b;
	float roc = rocAtPt(seed);
	TangentSpace(n, t, b);
#ifdef DEBUG
	std::cout << "Seed Value: " << m_scene.Evaluate(seed) << '\n';
	std::cout << "Roc: " << roc << '\n';
#endif
	m_container.m_vertices.push_back(seed);
	m_container.m_normals.push_back(n);
	m_container.m_vertRocs.push_back(roc);

	// Generate first front!

	Front* front = new Front();
	for (unsigned int i = 0; i < 6; ++i)
	{
		float x = 2.f * roc * std::cos(float(i) * 0.33333333f * M_PI);
		float y = 2.f * roc * std::sin(float(i) * 0.33333333f * M_PI);
		glm::vec3 proj_point = m_scene.Project(seed + (x*t) + (y*b));

		glm::vec3 normal = m_scene.Normal(proj_point);
		m_container.m_vertices.push_back(proj_point);
		m_container.m_normals.push_back(normal);
		m_container.m_vertRocs.push_back(rocAtPt(proj_point));

#ifdef DEBUG
		std::cout << "Point Value: " << m_scene.Evaluate(proj_point) << '\n';
		std::cout << "Field Value: " << m_scene.FieldValue(proj_point) << '\n';
		std::cout << "Normal Value: " << normal << '\n';
#endif

		unsigned int f_v_index = 1 + (i % 6);
		//front->pushVertex(f_v_index);

		front->appendVertex(f_v_index);
		PolyContainer::Face f;
		f.vert_index[0] = 0;
		f.vert_index[1] = 1 + (i % 6);
		f.vert_index[2] = 1 + ((i + 1) % 6);
		m_container.m_faces.push_back(f);
	}

	m_container.m_fronts.push_back(front);
	// Compute opening angles

	actualizeAngles();

	m_mesh_tree.buildIndex();
	m_front_tree.buildIndex();
}



void TrisPoly::actualizeAngles()
{
	Front* f = m_container.getFront();
	if (f == NULL) return;
	for (unsigned int i = 0; i < f->size(); ++i)
	{
		f->setOpeningAngle(i, computeOpenAngle(i, f));
		//f->setOpenAngle(i, computeOpenAngle(i, f));
	}
}

// Computes open angle from the values in the front
// ith vertex in the top front
// Everything is in radians
// Counter-clockwise
// The left is next
// the right is previous
float TrisPoly::computeOpenAngle(unsigned int i, const Front* f) const
{
	if (f == NULL) return 0;
	const unsigned int vi = f->getVertex(i);
	const glm::vec3 v = m_container.m_vertices[vi];
	const glm::vec3 n = m_container.m_normals[vi];
	const glm::vec3 vleft = m_container.m_vertices[f->getLeft(i)];
	const glm::vec3 vright = m_container.m_vertices[f->getRight(i)];

	glm::vec3 X, Y;
	TangentSpace(n, X, Y);
	glm::vec3 vleft_proj;
	glm::vec3 vright_proj;
	vleft_proj.x = glm::dot((vleft - v), X);
	vright_proj.x = glm::dot((v - vright), X);
	vleft_proj.y = glm::dot((vleft - v), Y);
	vright_proj.y = glm::dot((v - vright), Y);
	vleft_proj.z = 0;
	vright_proj.z = 0;
	vleft_proj = glm::normalize(vleft_proj);
	vright_proj = glm::normalize(vright_proj);


	float dot = clamp<float>(glm::dot(vleft_proj, vright_proj), -1.f, 1.f);
	float opening_angle;
	// Keep it on the exterior
	if ((glm::cross(vleft_proj, vright_proj)).z >= 0.f)
		opening_angle = M_PI - std::acos(dot);
	else opening_angle = M_PI + std::acos(dot);
	return opening_angle;
}

float TrisPoly::rocAtPt(const glm::vec3& v)
{
	float k1, k2;
	m_scene.Curvature(v, k1, k2);
	return 1.f/((std::max(std::abs(k1), std::abs(k2)))  * 10);
}

