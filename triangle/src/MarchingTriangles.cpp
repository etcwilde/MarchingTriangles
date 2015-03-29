/*
 * MarchingTriangles
 *
 * File: 	MarchingTriangles.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 16 2015
 */

#define DEPTH 1

#include "MarchingTriangles.hpp"

using namespace polygonizer;

MarchingTriangles::MarchingTriangles(Implicit::Object* obj) :
	Polygonizer(obj),
	m_growth(1),
	m_error(0)
{
	m_current_front = 0;
}

MarchingTriangles::MarchingTriangles(Implicit::Object* obj, float error):
	Polygonizer(obj),
	m_growth(1),
	m_error(error)
{
	m_current_front = 0;
}

MarchingTriangles::MarchingTriangles(Implicit::Object* obj, float error,
		float growth) :
	Polygonizer(obj),
	m_growth(growth),
	m_error(error)
{
	m_current_front = 0;
}



void MarchingTriangles::Polygonize()
{

}

void MarchingTriangles::SeedHexagon(const glm::vec3& seed)
{
	glm::vec3 T, B; // Tangent and Bi-normal

	// Check that the seed point is on the surface
	// If not, put it on the surface
	glm::vec3 point = seed;
	if (!f_equ(0.f, m_object->Evaluate(point)))
		point = m_object->Project(point);

	glm::vec3 normal = m_object->Normal(point);
	getTangentSpace(normal, T, B);

	/*for (unsigned int i = 0; i < 6; ++i)
	{

		m_mesh.AddFace(
	} */

}
