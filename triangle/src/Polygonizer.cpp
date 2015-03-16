/*
 * Polygonizer
 *
 * File: 	Polygonizer.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 3 2015
 */

#include "Polygonizer.hpp"

Polygonizer::Polygonizer(Implicit::Object *obj) :
	m_object(obj),
	m_mesh()
{
}

Explicit::Mesh Polygonizer::GetMesh()
{
	return m_mesh;
}

void Polygonizer::SetObject(Implicit::Object *obj)
{
	m_object = obj;
}


