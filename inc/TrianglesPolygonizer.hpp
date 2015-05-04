#ifndef TRIANGLESPOLYGONIZER_HPP
#define TRIANGLESPOLYGONIZER_HPP

#include <vector>
#include <stack>
#include <cmath>

#include <glm/glm.hpp>

#include "Polygonizer.hpp"


class PolygonizerVertex
{
public:
	PolygonizerVertex();
	~PolygonizerVertex();

	void addNeighbor(const PolygonizerVertex* new_neighbor);
	float getMinAngle();

protected:

private:
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
	~PolygonizerFront();
protected:
private:
	Implicit::Object& m_object;
	std::vector<PolygonizerVertex> m_vertex_stack;
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
class PolygonizerMesh
{
public:
	PolygonizerMesh(Implicit::Object& o);
	~PolygonizerMesh();

	Mesh toMesh();
protected:
private:
	std::stack<PolygonizerFront*> m_fronts;
	Implicit::Object& m_object;
};

/*
 * Generates the polygonizer meshes and the final mesh itself
 */
class TrianglePolygonizer : public Polygonizer
{
public:
	TrianglePolygonizer(Implicit::Object& o);
	TrianglePolygonizer(Implicit::Object& o, float growth_rate);
protected:
	virtual Mesh polygonize();
private:
	Implicit::Object& m_object; // The object being polygonized
	PolygonizerMesh m_mesh; // The mesh
	float m_growth_rate; // How much to scale by
}

#endif//TRIANGLESPOLYGONIZER_HPP
