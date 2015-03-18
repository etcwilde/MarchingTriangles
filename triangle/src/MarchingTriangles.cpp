/*
 * MarchingTriangles
 *
 * File: 	MarchingTriangles.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 16 2015
 */

#include "MarchingTriangles.hpp"

using namespace polygonizer;

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

	unsigned int depth = 0;
	while(depth <= DEPTH && m_front.size() > 0)
	{
#ifdef DEBUG
		std::cout << depth << '\n';
		std::cout << "Front size: " << m_front.size() << '\n';
#endif
		Edge e = m_front.pop_edge();
		std::cout << "Edge: " << e.pt1 << ", " << e.pt2 << '\n';

		glm::vec3 nextpt = e.midpoint();
		glm::vec3 T, B;
		getTangentSpace(m_object->Normal(nextpt), T, B);
		nextpt = m_object->Project(T * -0.2f * e.length() + nextpt);

		glm::vec3 n = m_object->Normal(nextpt);
		glm::vec3 n2 = m_object->Normal(e.pt1);
		glm::vec3 n3 = m_object->Normal(e.pt2);

		m_mesh.AddFace(nextpt, e.pt1, e.pt2, n, n2, n3);

		depth++;
	}
}

void MarchingTriangles::SeedTriangle()
{
	// Generate three vertices
	glm::vec3 start_vertex = m_object->GetStartVertex();

	// Find curvatures at the point
	glm::vec3 start_normal = m_object->Normal(start_vertex);

	float k1, k2;
	m_object->Curvature(start_vertex, k1, k2);

	glm::vec3 T;
	glm::vec3 B;

	getTangentSpace(start_normal, T, B);


	glm::vec3 p2 = m_object->Project(start_vertex + (T * 0.2f));
	glm::vec3 p3 = m_object->Project(((start_vertex + p2) / 2.f) + B * 0.2f);
	glm::vec3 p4 = m_object->Project(((start_vertex + p2) / 2.f) - B * 0.2f);

#ifdef DEBUG
	std::cout
		<< m_object->FieldValue(start_vertex) << '\t'
		<< m_object->FieldValue(p2) << '\t'
		<< m_object->FieldValue(p3) << '\n';
#endif
	Edge e1;
	e1.pt1 = start_vertex;
	e1.pt2 = p3;

	Edge e2;
	e2.pt1 = p2;
	e2.pt2 = p3;

	Edge e3;
	e3.pt1 = start_vertex;
	e3.pt2 = p4;

	Edge e4;
	e4.pt1 = p2;
	e4.pt2 = p4;

	m_front.push_edge(e1);
	m_front.push_edge(e2);
	m_front.push_edge(e3);
	m_front.push_edge(e4);

	glm::vec3 n2 = m_object->Normal(p2);
	glm::vec3 n3 = m_object->Normal(p3);
	glm::vec3 n4 = m_object->Normal(p4);
	m_mesh.AddFace(start_vertex, p2, p3, start_normal, n2, n3);
	m_mesh.AddFace(start_vertex, p2, p4, start_normal, n2, n4);
}


