/*
 * MarchingTriangles
 *
 * File: 	MarchingTriangles.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 16 2015
 */

#include "MarchingTriangles.hpp"

MarchingTriangles::MarchingTriangles(Implicit::Object* obj) :
	Polygonizer(obj),
	m_size(),
	m_growth(1),
	m_error(0)
{ }

MarchingTriangles::MarchingTriangles(Implicit::Object* obj, float error):
	Polygonizer(obj),
	m_size(),
	m_growth(1),
	m_error(error)
{ }

MarchingTriangles::MarchingTriangles(Implicit::Object* obj, float error,
		float growth) :
	Polygonizer(obj),
	m_size(),
	m_growth(growth),
	m_error(error)
{ }

void MarchingTriangles::Polygonize()
{
	SeedTriangle();
}

void MarchingTriangles::SeedTriangle()
{
	// Generate three vertices
	glm::vec3 start_vertex = m_object->GetStartVertex();
	glm::vec3 start_normal = m_object->Normal(start_vertex);
	glm::vec3 T;
	glm::vec3 B;

	getTangentSpace(start_normal, T, B);

	glm::vec3 p2 = m_object->Project(start_vertex + (T * 0.2f));
	glm::vec3 p3 = m_object->Project(start_vertex + (B * 0.2f));

#ifdef DEBUG
	std::cout
		<< m_object->FieldValue(start_vertex) << '\t'
		<< m_object->FieldValue(p2) << '\t'
		<< m_object->FieldValue(p3) << '\n';
#endif


	glm::vec3 n2 = m_object->Normal(p2);

	glm::vec3 n3 = m_object->Normal(p3);

	m_mesh.AddFace(start_vertex,
			p2, p3,
			start_normal,
			n2, n3);
}


