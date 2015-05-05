#ifndef TRIANGLESPOLYGONIZER_HPP
#define TRIANGLESPOLYGONIZER_HPP

#include <vector>
#include <stack>
#include <cmath>

#include <glm/glm.hpp>

#include "Polygonizer.hpp"
#include "Mesh.hpp"



/*
 * Calculates the angle between two points
 */
float angle(const glm::vec3& A, const glm::vec3 B);

/**
 * This is a vertex on the front
 *
 * Will always contain two neighboring vertices
 */
class PolygonizerVertex
{
public:
	PolygonizerVertex(const glm::vec3& p);
	//
	// Does not update the neighbors of the neighbors to include this
	// Will not check that the other neighbors are null or freed
	// You must free your neighboring vertices
	//
	void setNeighbors(const PolygonizerVertex* n1, const PolygonizerVertex* n2);

	const glm::vec3& Position() const;

	float getAngle() const;
protected:

private:
	const PolygonizerVertex* m_neighbors[2];
	glm::vec3 m_position;
};



/*
 * We need to quickly find verts with the smallest angle
 * -- Using a heap priority queue might be good
 * Front Requirements:
 * Split
 * Join
 *
 * Stores outer-most vertices and edges -- Removes worst
 */
class PolygonizerFront
{
public:
	PolygonizerFront(Implicit::Object& o);

	PolygonizerFront* Split();

	void Join(PolygonizerFront*);

	PolygonizerVertex* SeltIntersection(PolygonizerVertex);

	unsigned int size() const;
protected:
private:
	Implicit::Object& m_object;
	std::vector<PolygonizerVertex> m_vertex_heap;
};

/*
 * We need to be able to actually store all the information for the mesh that
 * is not on the front
 *
 * The innards don't matter quite as much as the front, but should still be
 * kept around.
 *
 * The front will be in a stack within this thing
 */
/*class PolygonizerMesh
{
public:
	PolygonizerMesh(Implicit::Object& o);
	~PolygonizerMesh();

	Mesh toMesh();
protected:
	void build(); // This is where the exciting stuff happens

	Triangulate(
private:
	std::stack<PolygonizerFront*> m_fronts;
	Implicit::Object& m_object;
}; */

/*
 * Generates the polygonizer meshes and the final mesh itself
 */
class TriPoly : public Polygonizer
{
public:
	TriPoly(Implicit::Object& o);
	TriPoly(Implicit::Object& o, float growth_rate);
	~TriPoly();

protected:
	virtual Mesh polygonize();

private:
	std::stack<PolygonizerFront*> m_fronts;
	Mesh m_mesh;
	float m_growth_rate; // How much to scale by
};

#endif//TRIANGLESPOLYGONIZER_HPP
