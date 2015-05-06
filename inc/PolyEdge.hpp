#ifndef POLYEDGE_HPP
#define POLYEDGE_HPP

#include "Mesh.hpp"

class Edge
{
public:
	Edge();
	Edge(unsigned int a, unsigned int b, const Mesh& m);

	void setEndpoints(unsigned int a, unsigned int b, const Mesh& m);

	unsigned int getEndpointIndex(unsigned short i) const;
	const glm::vec3& getEndpoint(unsigned short i) const;

private:
	unsigned int m_ia, m_ib;
	glm::vec3 m_a, m_b;
};

#endif//POLYEDGE_HPP
