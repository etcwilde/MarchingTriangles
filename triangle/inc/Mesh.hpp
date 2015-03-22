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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "vecHelp.hpp"
#include "Aabb.hpp"

/**
 * \brief Sets of defined vertices, normals, and faces making up shapes
 *
 */
namespace Geometry
{
	class Triangle
	{
	public:
		Triangle();

		Triangle(unsigned int v1, unsigned int v2, unsigned int v3,
				unsigned int n);

		Triangle(unsigned int v1, unsigned int v2, unsigned int v3,
				unsigned int n1, unsigned int n2, unsigned int n3);

		/**
		 * \brief Index on vertices
		 * \param index The vertex to get
		 * \return vertex index
		 * 0 - 2
		 *
		 * If index is greater than 2, it will take the modulus of
		 * three
		 */
		unsigned int operator[](unsigned int index) const;
		/**
		 * \brief Index on vertices
		 * \param index The vertex to get
		 * \return vertex index
		 * 0 - 2
		 *
		 * If index is greater than 2, it will take the modulus of
		 * three
		 */
		unsigned int vertex(unsigned int index) const;
		/**
		 * \brief Index on normals
		 * \param index The normal to get
		 * \return normal index
		 * 0 - 2
		 *
		 * If index is greater than 2, it will take the modulus of
		 * three
		 */
		unsigned int normal(unsigned int index) const;

		/**
		 * \brief returns the array of vertices for the triangle
		 * \return const unsigned int array of vertex indices
		 */
		const unsigned int* vertices() const;

		/**
		 * \brief returns the array of normal for the triangle
		 * \return const unsigned int array of normal indices
		 */
		const unsigned int* normals() const;

		bool set() const;

	private:
		bool m_set;
		unsigned int m_vertex[3];
		unsigned int m_normal[3];
	};

	class Mesh
	{
	public:
		Mesh();
		Aabb getBox();

		void addTriangle(const glm::vec3& v1,
				const glm::vec3& v2,
				const glm::vec3& v3,
				const glm::vec3& n);

		void setTransform(const glm::mat4& worldFromLocal);
	protected:
		Aabb getTriangleBox(unsigned int triangle_index) const;
	private:
		inline void drawTriangle(const Triangle& t);
		bool m_builtList;

		glm::mat4 m_worldFromLocal;
		glm::mat4 m_invTranspose;

		std::vector<Triangle> m_triangles;
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec3> m_smoothedNormals;
		std::vector<bool> m_boundary_vertex;
	};
};
#endif // MESH_HPP
