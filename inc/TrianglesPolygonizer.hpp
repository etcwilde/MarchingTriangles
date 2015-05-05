#ifndef TRIANGLESPOLYGONIZER_HPP
#define TRIANGLESPOLYGONIZER_HPP

#include <vector>
#include <stack>
#include <cmath>

#include <glm/glm.hpp>

#include "Polygonizer.hpp"
#include "Mesh.hpp"


class PolygonizerVertex
{
public:
	PolygonizerVertex(const glm::vec3& p);
	~PolygonizerVertex();

	/**
	 * \brief Adds a new neighbor to this vertex
	 * This does not add this vertex to the other vertex neighbor groups
	 * YOU MUST DO THIS
	 *
	 * \param new_neighbor The address of the node which is the new
	 * neighbor
	 */
	void addNeighbor(const PolygonizerVertex* new_neighbor);

	float getMinAngle();

protected:

private:
	// Should be 2 neighbors maximum
	std::vector<const PolygonizerVertex*> m_neighbors;
	glm::vec3 m_position;
};

/*
 * We need to quickly find vers with the smallest angle
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
	//~PolygonizerFront();
	
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
class TrianglePolygonizer : public Polygonizer
{
public:
	TrianglePolygonizer(Implicit::Object& o);
	TrianglePolygonizer(Implicit::Object& o, float growth_rate);
	~TrianglePolygonizer();
protected:
	virtual Mesh polygonize();
private:
	std::stack<PolygonizerFront*> m_fronts;
	Mesh m_mesh;
	float m_growth_rate; // How much to scale by
};

#endif//TRIANGLESPOLYGONIZER_HPP
