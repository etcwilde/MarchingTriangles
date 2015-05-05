#include "Polygonizer.hpp"
Polygonizer::Polygonizer(Implicit::Object& scene) :
	m_scene(scene),
	m_cache_mesh_set(false),
	m_cache_mesh()
{ }

Mesh Polygonizer::Polygonize()
{
	if(!m_cache_mesh_set)
	{
		m_cache_mesh = polygonize();
		m_cache_mesh_set = true;
	}
	return m_cache_mesh;
}
