#include "Polygonizer.hpp"

Polygonizer::Polygonizer(Implicit::Object& scene) :
	m_scene(scene),
	m_mesh_set(false),
	m_mesh()
{ }

Mesh Polygonizer::Polygonize()
{
	if(!m_mesh_set)
	{
		m_mesh = polygonize();
		m_mesh_set = true;
	}
	return m_mesh;
}
