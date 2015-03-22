/*
 * Mesh
 *
 * File: 	Mesh.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 12 2015
 */

#include "Mesh.hpp"

using namespace Geometry;

/*
 * Triangle Data
 */

Triangle::Triangle() :
	m_set(false)
{ }

Triangle::Triangle(unsigned int v1, unsigned int v2, unsigned int v3,
				unsigned int n) :
	m_set(true)
{
       	m_vertex[0] = v1;
	m_vertex[1] = v2;
	m_vertex[2] = v3;
	m_normal[0] = n;
	m_normal[1] = n;
	m_normal[2] = n;

}

Triangle::Triangle(unsigned int v1, unsigned int v2, unsigned int v3,
		unsigned int n1, unsigned int n2, unsigned int n3) :
	m_set(true)
{
       	m_vertex[0] = v1;
	m_vertex[1] = v2;
	m_vertex[2] = v3;
	m_normal[0] = n1;
	m_normal[1] = n2;
	m_normal[2] = n3;

}

unsigned int Triangle::operator[](unsigned int index) const
{
	return m_vertex[index % 3];
}

unsigned int Triangle::vertex(unsigned int index) const
{
	return m_vertex[index % 3];
}

unsigned int Triangle::normal(unsigned int index) const
{
	return m_normal[index % 3];
}

const unsigned int* Triangle::vertices() const
{
	return m_vertex;
}

const unsigned int* Triangle::normals() const
{
	return m_normal;
}

bool Triangle::set() const
{
	return m_set;
}

/*
 * Mesh Data
 */
Mesh::Mesh() :
	m_builtList(false),
	m_worldFromLocal(),
	m_invTranspose(),
	m_triangles(),
	m_vertices(),
	m_normals()
{
	setTransform(m_worldFromLocal);
}

void Mesh::addTriangle(const glm::vec3& v1, const glm::vec3& v2,
			const glm::vec3& v3, const glm::vec3& n)
{
	unsigned int vi1, vi2, vi3;
	unsigned int ni;
	vi1 = m_vertices.size();
	m_vertices.push_back(v1);
	vi2 = m_vertices.size();
	m_vertices.push_back(v2);
	vi3 = m_vertices.size();
	m_vertices.push_back(v3);

	ni = m_normals.size();
	m_normals.push_back(n);


}

Aabb Mesh::getBox()
{
	Aabb aabb;
	for (unsigned int i = 0; i < m_triangles.size(); ++i)
		aabb.add(getTriangleBox(i));
	return aabb;
}

void Mesh::setTransform(const glm::mat4& worldFromLocal)
{
	m_worldFromLocal = worldFromLocal;
	m_invTranspose = glm::inverseTranspose(worldFromLocal);
}

Aabb Mesh::getTriangleBox(unsigned int ti) const
{
	Aabb aabb;
	const Triangle& t = m_triangles[ti];
	glm::vec3 v1 = m_vertices[t[0]];
	glm::vec3 v2 = m_vertices[t[1]];
	glm::vec3 v3 = m_vertices[t[2]];
	v1 = glm::vec3(m_worldFromLocal * glm::vec4(v1, 1));
	v2 = glm::vec3(m_worldFromLocal * glm::vec4(v2, 1));
	v3 = glm::vec3(m_worldFromLocal * glm::vec4(v3, 1));

	aabb.include(v1); aabb.include(v2); aabb.include(v3);
	return aabb;
}


