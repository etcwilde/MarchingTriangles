/*
 * Polygonizer
 *
 * File: 	Polygonizer.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 3 2015
 */

#include "Polygonizer.hpp"

using namespace polygonizer;

Polygonizer::Polygonizer(Implicit::Object *obj) :
	m_object(obj),
	m_mesh(),
	m_mesh_good(false)

{
}

Explicit::Mesh Polygonizer::GetMesh()
{
	if (!m_mesh_good)
		Polygonize();
	return m_mesh;
}

void Polygonizer::SetObject(Implicit::Object *obj)
{
	m_mesh_good = false;
	m_object = obj;
}

void Polygonizer::getTangentSpace(const glm::vec3& N, glm::vec3& T, glm::vec3& B)
	const
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}

