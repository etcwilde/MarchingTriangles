#ifndef POLYTRIS_HPP
#define POLYTRIS_HPP

#include "implicit/ImplicitSystem.hpp"
#include "Polygonizer.hpp"
#include "PolyTris.hpp"
#include "PolyFront.hpp"
#include "Mesh.hpp"
#include "utils/GeoCore.hpp"
#include "utils/MathCore.hpp"
#include "nanoflann.hpp"

#include "PolyEdge.hpp"

#include <list>
#include <vector>
#include <stack>

#include <glm/glm.hpp>

// Curvature Dependent Marching Triangles Polygonizer
class TrisPoly : public Polygonizer
{
public:
	// Mush Have
	TrisPoly(Implicit::Object& o);

	unsigned int verts() const { return m_vertices.size(); }
	unsigned int edges() const { return m_edges.size(); }
	unsigned int fronts() const { return m_fronts.size(); }

	const glm::vec3& getVertex(unsigned int index) const;
	const Edge& getEdge(unsigned int index) const;
	const Front* getFront(unsigned int index) const;



protected:
	// Must have
	virtual Mesh polygonize();
private:
	//Methods

	// Generates a hexagon from a seed vertex
	// adds generated front to fronts
	void seedHexagon(const glm::vec3& start);

	Front* mergeFronts(Front* A, unsigned int a, Front* B, unsigned int b);
	void splitFronts(Front* F, Front* A, unsigned int a, Front* B, unsigned int b);

	// Only works on fronts with 3 or 4 vertices (a hole)
	void fill(Front* f);

private:
	// Variables
	Mesh m_mesh;

	std::vector<glm::vec3> m_vertices;
	std::vector<Edge> m_edges;
	std::stack<Front*> m_fronts;

};


#endif//POLYTRIS_HPP
