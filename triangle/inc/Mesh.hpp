/**
 * Mesh
 *
 * File: 	Mesh.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 12 2015
 */

#ifndef MESH_HPP
#define MESH_HPP

#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <glm/vec3.hpp>


namespace Explicit
{
	/**
	 * \brief Explicit Face
	 * A face is a single triangle
	 */
	class Face
	{
	public:
		Face();
		unsigned int m_vertex_index[3]; // index of each vertex
		unsigned int m_normal_index[3]; // normal of each vertex
	};

	class Mesh
	{
	public:
		Mesh();

		/**
		 * \brief Writes object data to obj file
		 *
		 * Writes to "output.obj"
		 *
		 * Will overwrite if it already exists
		 */
		void Export();

		std::vector<glm::vec3> m_vertex_atlas;
		std::vector<glm::vec3> m_normal_atlas;
		std::list<Face> m_faces;

	protected:
	private:
	};
};
#endif // MESH_HPP
