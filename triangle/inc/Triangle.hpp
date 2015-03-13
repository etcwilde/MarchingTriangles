/*
 * Triangle
 *
 * File: 	Triangle.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 03 2015
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/vec3.hpp>

#include <list>

using namespace glm;

class Triangle
{
public:
	Triangle(vec3 p1, vec3 p2, vec3 p3) :
		vertex_1(p1),
		vertex_2(p2),
		vertex_3(p3) {}

	std::list<glm::vec3> get_vertices();

	void Draw();
private:
	vec3 vertex_1;
	vec3 vertex_2;
	vec3 vertex_3;
};

#endif
