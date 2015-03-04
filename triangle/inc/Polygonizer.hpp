/**
 * Polygonizer
 *
 * File: 	Polygonizer.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#ifndef POLYGONIZER_H
#define POLYGONIZER_H

#include <list>
#include <vector>
using std::list;

#include "ImplicitSystem.hpp"
#include "Triangle.hpp"

#define MAX_ITERS	20

#include <iostream>

class Polygonizer
{
public:
	Polygonizer(Implicit::Object* object);
	Polygonizer(Implicit::Object* object, float iso);
	Polygonizer(Implicit::Object* object, float iso, float scale);

	list<Triangle> polygonize(list<glm::vec3> seed_points);

	list<Triangle> polygonize();

protected:
	void seedHexagon(glm::vec3 seed);
	glm::vec3 project(glm::vec3 point, float tolerance);

	glm::vec3 drop_to_surface(glm::vec3 point, float tolerance);

	glm::vec3 gradient(const glm::vec3& pt); // Slope -- 3D derivative
	glm::mat3 hessian(const glm::vec3& pt); // Curvature -- 3D second deriv
	void getDeltas(float &hx, float &hy, float &hz, const glm::vec3& pt, float eps);

	float derivative(glm::vec3 pt);

	void computeTangent(const glm::vec3& N, glm::vec3& T, glm::vec3& B);
	void curvature(const glm::vec3& p, float& k1, float& k2);

private:

	glm::mat3 adjoint(const glm::mat3& F);

	float m_iso;

	Implicit::Object* m_object;
	float m_tolerance;
	float m_scale; // How much to grow or shrink -- default 1
	list<Triangle> m_triangles;
	list<glm::vec3> m_seeds;
};


#endif //POLYGONIZER_H
