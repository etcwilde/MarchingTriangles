#include "TrianglesPolygonizer.hpp"

float angle(const glm::vec3& A, const glm::vec3 B)
{

	return std::acos(glm::dot(A, B) / (glm::length(A) * glm::length(B)));
}

/*
 * Polygonizer Vertex
 */

PolygonizerVertex::PolygonizerVertex(const glm::vec3& p) :
	m_neighbors(),
	m_position(p)
{ }

void PolygonizerVertex::setNeighbors(const PolygonizerVertex* n1,
		const PolygonizerVertex* n2)
{
	m_neighbors[0] = n1;
	m_neighbors[1] = n2;
}

float PolygonizerVertex::getAngle() const
{
	return angle(m_neighbors[0]->Position() - m_position,
			m_neighbors[1]->Position() - m_position);
}

const glm::vec3& PolygonizerVertex::Position() const
{
	return m_position;
}

/*
 * Polygonizer Front
 */

PolygonizerFront::PolygonizerFront(Implicit::Object& o) :
	m_object(o),
	m_vertex_heap()
{ }

unsigned int PolygonizerFront::size() const
{
	return m_vertex_heap.size();
}


/*
 * Triangle Polygonizer Content
 */
TriPoly::TriPoly(Implicit::Object& o) :
	Polygonizer(o),
	m_fronts(),
	m_mesh(),
	m_growth_rate(1.f)
{ }

TriPoly::TriPoly(Implicit::Object& o, float growth_rate) :
	Polygonizer(o),
	m_fronts(),
	m_mesh(),
	m_growth_rate(growth_rate)
{ }

TriPoly::~TriPoly()
{
	if (m_fronts.size() > 0)
	{
		std::cerr << "Fronts not cleared Properly\n";
		std::cerr << "Missed " << m_fronts.size() << " fronts\n";
		while (m_fronts.size() > 0)
		{
			delete m_fronts.top();
			m_fronts.pop();
		}
	}
}

// Polygonization pseudo code found in
// Curvature Dependent polygonization of Implicit surfaces
// Bruno Rodrigues De Araujo and Joaquim Armando Pires Jorge
Mesh TriPoly::polygonize()
{

	glm::vec3 seed = m_scene.GetStartVertex();
	PolygonizerFront* f0;
	m_fronts.push(new PolygonizerFront(m_scene));
	// Mesh is already initialized and empty
	while (m_fronts.size() > 0)
	{
		f0 = m_fronts.top();
		m_fronts.pop();
		while (f0->size() > 3)
		{
			// Actualize angles

		}

	}
	return m_mesh;
}

