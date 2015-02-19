/**
 * MarchingCubes
 *
 * File: 	MarchingCubes.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#include "MarchingCubes.hpp"

using namespace Polygonizer;
using namespace glm;
using namespace Implicit;

MarchingCubes::MarchingCubes(Object* obj) :
	m_object(obj),
	m_voxels(),
	m_drawable_voxels(),
	m_vertex_data(),
	m_vertex_count(0),
	m_dirty(false),
	m_voxelsize(0.05f),
	m_field_threshold(0.5f)
{ }

