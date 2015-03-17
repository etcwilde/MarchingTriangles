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
	/**
	 * \brief Creates a new polygonizer instance
	 *
	 * \param obj Object to be polygonized
	 */
	Polygonizer(Implicit::Object *obj);

	/**
	 * \brief gets the converted mesh
	 * \return Finalized mesh
	 */
	Explicit::Mesh GetMesh();

	/**
	 * \brief Set the instance object
	 *
	 * \param obj New object to polygonize
	 */
	void SetObject(Implicit::Object* obj);

protected: // protected Methods
	/**
	 * Creates the mesh from the given object
	 *
	 * Updates the instance variable m_mesh
	 * Any input is taken from m_object
	 * m_object should not be changed by this method
	 *
	 */
	virtual void Polygonize()=0;

	/**
	 * \brief Generate Tangent space
	 * Generates the tangent space of a given normal vector
	 *
	 * \param N The normal vector to find tangent space of
	 * \param T Where the tangent will be stored
	 * \param B Where the binormal will be stored
	 */
	void getTangentSpace(const glm::vec3& N, glm::vec3& T,
			glm::vec3& B) const;

protected: // Protected Data structures

	Implicit::Object* m_object;
	Explicit::Mesh m_mesh;

private:
	bool m_mesh_good;
};

#endif //POLYGONIZER_H
