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
	while(depth < DEPTH && m_front.size() > 0)
	{
#ifdef DEBUG
		std::cout << "Polygonization Depth: " << depth << '\n';
		std::cout << "Front size: " << m_front.size() << '\n';
#endif
		Edge e = m_front.pop_edge();

#ifdef DEBUG
		std::cout << "Edge: " << e.pt1 << ", " << e.pt2 << '\n';
#endif
		glm::vec3 p1 = e.pt1;
		glm::vec3 p2 = e.pt2;
		glm::vec3 n1 = m_object->Normal(p1);
		glm::vec3 n2 = m_object->Normal(p2);
		glm::vec3 T, B;
		getTangentSpace(n1, T, B);
		glm::vec3 p3;
		if (glm::dot(T, e.direction()) < 0)
			p3 = m_object->Project(((p1 + p2) / 2.f) + (T * -0.2f));
		else
			p3 = m_object->Project(((p1 + p2) / 2.f) + (T * 0.2f));

		m_mesh.AddFace(p1, p2, p3, n1, n2, m_object->Normal(p3));

		m_front.push_edge(Edge(p1, p3));
		//m_front.push_edge(Edge(p3, p2));

#ifdef DEBUG
	std::cout
		<< m_object->FieldValue(p1) << '\t'
		<< m_object->FieldValue(p2) << '\t'
		<< m_object->FieldValue(p3) << '\n';
#endif
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
	// glm::vec3 p4 = m_object->Project(((start_vertex + p2) / 2.f) - B * 0.2f);

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
	e2.pt2 = p2;
	e2.pt1 = p3;

	/* Edge e3;
	e3.pt2 = start_vertex;
	e3.pt1 = p4;

	Edge e4;
	e4.pt1 = p2;
	e4.pt2 = p4; */

	m_front.push_edge(e1);
	m_front.push_edge(e2);

	glm::vec3 n1 = m_object->Normal(start_vertex);
	glm::vec3 n2 = m_object->Normal(p2);
	glm::vec3 n3 = m_object->Normal(p3);

#ifdef DEBUG
	std::cout << "Triangle 1: " << start_vertex << ", "
		<< p2 << ", "
		<< p3 << ". "
		<< n1 << ", " << n2 << ", " << n3 << '\n';

/*	std::cout << "Triangle 2: " << start_vertex << ", "
		<< p4 << ", "
		<< p2 << ". "
		<< n1 << ", " << n4 << ", " << n2 << '\n'; */
#endif
	m_mesh.AddFace(start_vertex, p2, p3, n1, n2, n3);
}


