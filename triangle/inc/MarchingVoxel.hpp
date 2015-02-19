/**
 * MarchingVoxel
 *
 * File: 	MarchingVoxel.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#ifndef MARCHING_VOXEL_H
#define MARCHING_VOXEL_H

//Polygonizer hash table
#define	NBITS 	5
#define	BMASK 	0x037
#define	HASH(a, b, c) 	((a&BMASK) << NBITS | (b&BMASK) ) << NBITS|(c&BMASK)
#define HSIZE	1<<NBITS*3

#define	BACK_BOTTOM_LEFT	0
#define BACK_BOTTON_RIGHT	1
#define BACK_TOP_RIGHT		2
#define BACK_TOP_LEFT		3
#define FRONT_BOTTOM_LEFT	4
#define FRONT_BOTTOM_RIGHT	5
#define FRONT_TOP_RIGHT		6
#define FRONT_TOP_LEFT		7
#define VERTEX_MASK		255

#define TOP_FACE		204
#define BOTTOM_FACE		51
#define LEFT_FACE		153
#define RIGHT_FACE		102
#define FRONT_FACE		240
#define BACK_FACE		15

#define	VISITED		512
#define TESTED		1024
#define GARBAGE		2048

#include <glm/vec3.hpp>
#include "Color.hpp"

using namespace glm;

namespace Polygonizer
{
	class VertexData
	{
	public:
		VertexData() : initialized(false) {}
		bool initialized;
		vec3 position;
		vec3 normal;
		ColorRGB color;
	};


	class MarchingVoxel
	{
	public:
		MarchingVoxel() :
			m_x(-1),
			m_y(-1),
			m_z(-1),
			m_flags(0),
			m_fields()
		{
			m_fields[0] = 0.0f;
			for (int i = 0; i < 12; i++) {m_vertexData[i] = NULL;}
		}

		MarchingVoxel(int x, int y, int z) :
			m_x(x),
			m_y(y),
			m_z(z),
			m_flags(0),
			m_fields()
		{
			m_fields[0] = 0.0f;
			for (int i = 0; i < 12; i++) {m_vertexData[i] = NULL;}
		}

		MarchingVoxel(vec3 vector) :
			m_x(vector.x),
			m_y(vector.y),
			m_z(vector.z),
			m_flags(0),
			m_fields()
		{
			m_fields[0] = 0.0f;
			for (int i = 0; i < 12; i++) {m_vertexData[i] = NULL;}
		}

		int x() const { return m_x; }
		int y() const { return m_y; }
		int z() const { return m_z; }
		bool visited() const { return (m_flags & VISITED) == VISITED; }
		bool tested() const { return (m_flags & TESTED) == TESTED; }
		bool garbage() const { return (m_flags & GARBAGE) == GARBAGE; }
		float field(int corner) const { return m_fields[corner]; }
		unsigned int corners() const {return m_flags & VERTEX_MASK; }
		VertexData* vertex(int edge) const {return m_vertexData[edge];}

		void setVisited() {m_flags = m_flags | VISITED; }
		void setTested() {m_flags = m_flags | TESTED; }
		void setGarbage() {m_flags = m_flags | GARBAGE; }
		void setField(int corner, float field){m_fields[corner]=field;}
		void setCorners(int corners)
		{m_flags = m_flags|(corners&VERTEX_MASK);}
		void setVertex(int edge, VertexData* vert)
		{m_vertexData[edge]=vert;}
		void mutateVoxel(int x, int y, int z){m_x = x; m_y=y; m_z=z;}
		void mutateVoxelOffset(int x, int y, int z)
		{m_x += x; m_y += y; m_z += z;}

	private:
		int m_x;
		int m_y;
		int m_z;
		unsigned int m_flags;
		float m_fields[8];
		VertexData *m_vertexData[12];
	};

	inline bool operator==(const MarchingVoxel& v1, const MarchingVoxel& v2)
	{
		return (v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z());
	}

	inline uint Hash(const MarchingVoxel& key)
	{
		return HASH(key.x(), key.y(), key.z());
	}
};

#endif //MARCHING_VOXEL_H
