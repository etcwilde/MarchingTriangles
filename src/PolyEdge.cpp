#include "PolyEdge.hpp"

Edge::Edge() :
	m_ia(0),
	m_ib(0)
{ }

Edge::Edge(unsigned int a, unsigned int b, const Mesh& m) :
	m_ia(a),
	m_ib(b),
	m_a(m.get_vertex(a)),
	m_b(m.get_vertex(b))
{ }

void Edge::setEndpoints(unsigned int a, unsigned int b, const Mesh& m)
{
	m_ia = a;
	m_ib = b;
	m_a = m.get_vertex(a);
	m_b = m.get_vertex(b);
}

unsigned int Edge::getEndpointIndex(unsigned short i) const
{
	return (i == 0) ? m_ia : m_ib;
}

const glm::vec3& Edge::getEndpoint(unsigned short i) const
{
	return (i == 0) ? m_a : m_b;
}
