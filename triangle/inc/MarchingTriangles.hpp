/*
 * MarchingTriangles
 *
 * File: 	MarchingTriangles.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 16 2015
 */

#ifndef MARCHING_TRIANGLES_HPP
#define MARCHING_TRIANGLES_HPP

#include "Polygonizer.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <list>
#include <stack>

#ifdef DEBUG
#include <iostream>
#endif

#define DEPTH 10

namespace polygonizer
{


/**
 * \brief Edge
 *
 * An edge is defined by two points
 */
class Edge
{
public:
	glm::vec3 pt1;
	glm::vec3 pt2;

	float length()
	{
		return glm::length(pt1 - pt2);
	}

	glm::vec3 midpoint()
	{
		return glm::vec3((pt1 + pt2) / 2.f);
	}

	glm::vec3 direction()
	{
		return glm::normalize(pt1 - pt2);
	}
};

class Front
{
public:
	std::list<Edge> edges;

	inline void push_edge(Edge e)
	{
		edges.push_back(e);
	}

	inline Edge peek()
	{
		return edges.front();
	}

	inline Edge pop_edge()
	{
		Edge e = peek();
		edges.erase(edges.begin());
		return e;
	}

	unsigned int size()
	{
		return edges.size();
	}

	// TODO:
	// self collisions
	// Get point at minimal angle
	// Front collision
	// Expand
	// Unify fronts
	// split fronts
	// triangulate mesh
	// Delete Front
};



/**
 * \brief A marching triangles advancing front polygonizer
 * Uses the marching triangles algorithm to generate a mesh given an implicit 
 * object.
 */
class MarchingTriangles : public Polygonizer
{
public:
	MarchingTriangles(Implicit::Object* obj);
	MarchingTriangles(Implicit::Object* obj, float error);
	MarchingTriangles(Implicit::Object* obj, float error, float growth);
protected:

	void SeedTriangle();

	void Polygonize();

	float m_size; // Generated by start

	// Not sure which is a better metric for generating better meshes
	float m_growth; //Default 1
	float m_error; //The epsilon used for calculations
	float m_max_curvature;
	// If error == 0, then use growth exclusively -- Not sure what I'm
	// talking about

	//std::list<Front> m_front;
	Front m_front;
};

};

#endif //MARCHING_TRIANGLES_HPP
