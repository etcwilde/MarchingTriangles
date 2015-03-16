/*
 * Polygonizer
 *
 * File: 	Polygonizer.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#ifndef POLYGONIZER_H
#define POLYGONIZER_H

#include "Mesh.hpp"
#include "ImplicitSystem.hpp"

#include <glm/glm.hpp>

#include <list>
#include <vector>
#include <stack>


// Generalized Polygonizer
class Polygonizer
{
public:
	// Given an object, builds a mesh
	Polygonizer(Implicit::Object *obj);

	// Get the mesh
	Explicit::Mesh GetMesh();

	void SetObject(Implicit::Object* obj);

protected: // protected Methods
	/**
	 * Creates the mesh from the given object
	 */
	virtual void Polygonize()=0;

protected: // Protected Data structures
		struct edge
		{
		public:
			glm::vec3 pt1; glm::vec3 pt2;
			inline float length()
			{ return glm::length(pt1 - pt2); };

			inline glm::vec3 direction()
			{ return glm::normalize(pt1 - pt2); };
		};

	Implicit::Object* m_object;
	Explicit::Mesh m_mesh;
private:
};

#endif //POLYGONIZER_H
