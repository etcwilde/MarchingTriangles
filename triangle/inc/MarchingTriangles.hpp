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

#include "floatlibs.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <list>
#include <stack>

#ifdef DEBUG
#include <iostream>
#endif

/*
 * Marching Triangles Advancing front algorithm
 *
 * Initialization steps:
 * Find seed point (implicit system) -- This won't be enough if the implicit is
 * broken into disjoint sets
 *
 *
 * Create bridging struts between two two triangles sticking out
 * 1--2--3
 * \ / \ /
 *  4   6
 *
 * Create an edge between vertex 4 and 6
 *
 *
 */

namespace polygonizer
{

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

	void Polygonize();

	void SeedHexagon(const glm::vec3& seed);

	// Not sure what is the best metric
	float m_growth;
	float m_error;
	float m_max_curvature;

	unsigned int m_current_front;
};

};

#endif //MARCHING_TRIANGLES_HPP
