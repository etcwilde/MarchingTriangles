/*
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
#include <stack>
#include <fstream>
#include <vector>
#include <thread>

#include <glm/vec3.hpp>

#include "Triangle.hpp"
#include "vecHelp.hpp"

/**
 * \brief Sets of defined vertices, normals, and faces making up shapes
 *
 */
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

	/**
	 * \brief Explicit Mesh
	 * A set of vertices, normals, and Faces
	 */
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

		/**
		 * \brief Adds a new face to the mesh
		 *
		 * A face must be made of three vertices and three normals
		 *
		 * \param v1 Vertex 1
		 * \param v2 Vertex 2
		 * \param v3 Vertex 3
		 *
		 * \param n1 Normal 1
		 * \param n2 Normal 2
		 * \param n3 Normal 3
		 */
		void AddFace(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
				glm::vec3 n1, glm::vec3 n2, glm::vec3 n3);

		/**
		 * \brief Draws the mesh
		 *
		 * This will get removed when we work in getting it to the vbo
		 */
		void Draw();

	protected:

		/**
		 * \brief Adds vertex to the vertex atlas
		 * \param vertex Vertex to be added to the atlas
		 */
		void push_vertex(glm::vec3 vertex);

		/**
		 * \brief Adds normal to the normal atlas
		 * \param normal Normal to be added to the atlas
		 */
		void push_normal(glm::vec3 normal);

		/**
		 * \brief Adds a face to the list of faces
		 * \param face The face to be pushed to the list
		 */
		void push_face(Face face);

		/**
		 * \brief Returns the number of vertices stored in the mesh
		 * \return size of vertex atlas
		 */
		unsigned int vertices() const;

		/**
		 * \brief Returns the number of normal stored in the mesh
		 * \return size of normal atlas
		 */
		unsigned int normals() const;

		/**
		 * \brief Returns the number of faces stored in the mesh
		 * \return number of faces
		 */
		unsigned int faces() const;

		/**
		 * \brief cleans Datastructures to ensure no duplicates
		 *
		 * This removes any duplicate vertices and fixes the index in
		 * the face
		 *
		 * Removes duplicate normals and fixes the index in the face
		 *
		 * Removes any duplicate faces
		 *
		 * This is a very hard problem
		 */
		void clean();

	private:
		typedef struct
		{
			unsigned int i;
			unsigned int j;
		} int_tup;

		void clean_verts();

		void clean_norms();

		void clean_faces();

		std::vector<glm::vec3> m_vertex_atlas;
		std::vector<glm::vec3> m_normal_atlas;
		std::list<Face> m_faces;


	};
};
#endif // MESH_HPP
