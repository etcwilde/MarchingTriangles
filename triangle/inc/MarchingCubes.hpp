/**
 * MarchingCubes
 *
 * File: 	MarchingCubes.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include "MarchingVoxel.hpp"
#include "ImplicitObject.hpp"

#include <map>
#include <list>

using namespace glm;
using namespace Implicit;

namespace Polygonizer
{
	class MarchingCubes
	{
	public:
		MarchingCubes(Object* obj);
		MarchingCubes(Object* obj, float voxel_size);
		~MarchingCubes();
		void setObject(Object* obj);
		void setDirty();
		void Draw();
		void setVoxelSize(float size);
		void setFieldThreshold(float thresh);
	protected:
	private:
		void initialize();
		void voxelize();
		void polygonize();

		void findFirstVoxel(MarchingVoxel* start_voxel);
		MarchingVoxel* findVoxel(const MarchingVoxel &voxel);
		MarchingVoxel* find_create_voxel(const MarchingVoxel & voxel);
		float getFieldValue(MarchingVoxel* voxel);
		bool isInObjects(MarchingVoxel* voxel);

		void draw();

		vec3 interpolateVertex(vec3 v1, vec3 v2, float f1, float f2);

		Object* m_object;



		std::map<uint, MarchingVoxel*> m_voxels;
		std::list<MarchingVoxel*> m_drawable_voxels;
		std::list<VertexData*> m_vertex_data;

		unsigned int m_vertex_count;
		bool m_dirty;

		float m_voxelsize;
		float m_field_threshold;

		struct corneroffset_t
		{
			int o_x;
			int o_y;
			int o_z;
		};

		const static corneroffset_t m_cornerOffset[];

		struct facemaps_t
		{
			int face;
			int o_x;
			int o_y;
			int o_z;
		};

		const static facemaps_t m_faceOffsetMap[];

		struct edgadjmap_t
		{
			int f1;
			int e1;
			int f2;
			int e2;
		};

		const static edgadjmap_t m_edgeAdjacentMap[];

		struct edgemap_t
		{
			int v1;
			int v2;
			int mask;
		};

		const static edgemap_t m_edgeMap[];

		struct polygonmap_t
		{
			int count;
			int polygons[15];
		};
		const static polygonmap_t m_polygonMap[];
	};
};

#endif //MARCHING_CUBES_H
