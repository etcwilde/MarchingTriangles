#ifndef POLYTRIS_HPP
#define POLYTRIS_HPP

#include "implicit/ImplicitSystem.hpp"
#include "Polygonizer.hpp"
#include "PolyTris.hpp"
#include "PolyFront.hpp"
#include "PolyEdge.hpp"
#include "Mesh.hpp"
#include "utils/GeoCore.hpp"
#include "utils/MathCore.hpp"
#include "nanoflann.hpp"


#include <list>
#include <vector>
#include <stack>
#include <cmath>

#include <glm/glm.hpp>

class PolyContainer
{
public:
	PolyContainer() { }

	unsigned int verts() const { return m_vertices.size(); }
	unsigned int edges() const { return m_edges.size(); }
	unsigned int fronts() const { return m_fronts.size(); }

	const glm::vec3& getVertex(unsigned int index) const
	{ return m_vertices[index]; }

	const Edge& getEdge(unsigned int index) const
	{ return m_edges[index]; }

	// Gets the top front
	Front* getFront() const
	{
		if (m_fronts.size() > 0) return m_fronts.back();
		else return NULL;

	}

	Front* getFront(unsigned int index) const
	{
		if (m_fronts.size() > index) return m_fronts[index];
		else return NULL;
	}

	Front* getFront() { return m_fronts.back(); }


	void popFront() { m_fronts.pop_back(); }

	typedef struct
	{
		unsigned int vert_index[3];
	} Face;


	// Direct access is good
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<float> m_vertRocs;
	std::vector<Edge> m_edges;
	std::vector<Front*> m_fronts;
	std::vector<Face> m_faces;
};


// For translating the mesh points to a kdtree
class MeshPtAdaptor
{
public:
	MeshPtAdaptor(const PolyContainer& poly): m_pts(poly) { }

	inline unsigned int kdtree_get_point_count() const
	{ return m_pts.verts(); }

	inline float kdtree_distance(const float* p1, const unsigned int index,
			unsigned int) const
	{
		return glm::length(glm::vec3(p1[0], p1[1], p1[2]) - m_pts.getVertex(index));
	}

	inline float kdtree_get_pt(const unsigned int i, int dim) const
	{
		if(dim == 0) return m_pts.getVertex(i).x;
		else if(dim == 1) return m_pts.getVertex(i).y;
		else return m_pts.getVertex(i).z;
	}

	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }

private:
	const PolyContainer& m_pts;

};

// Translating the front points to a kd tree
class FrontPtAdaptor
{
public:
	FrontPtAdaptor(const PolyContainer& poly) : m_pts(poly) { }

	inline unsigned int kdtree_get_point_count() const
	{
		return (m_pts.getFront() ) ? m_pts.getFront()->verts() : 0;
	}

	inline float kdtree_distance(const float* p1, const unsigned int index, unsigned int) const
	{
		/*return glm::length(
				glm::vec3(p1[0], p1[1], p1[2]) -
				m_pts.getVertex(m_pts.getFront()->getVertex(index))); */
		if (m_pts.getFront())
		{
			return glm::length(glm::vec3(p1[0], p1[1], p1[2]) -
					m_pts.getVertex(m_pts.getFront()->getVertex(index)));
		}
		else return 0;
	}


	inline float kdtree_get_pt(const unsigned int i, int dim) const
	{
		if (dim == 0) return m_pts.getVertex(m_pts.getFront()->getVertex(i)).x;
		else if (dim == 1) return m_pts.getVertex(m_pts.getFront()->getVertex(i)).y;
		else return m_pts.getVertex(m_pts.getFront()->getVertex(i)).z;
	}

	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const {return false;}

private:
	const PolyContainer& m_pts;
};

// Mesh Pt tree
typedef nanoflann::KDTreeSingleIndexAdaptor<
	nanoflann::L2_Simple_Adaptor<float, MeshPtAdaptor>,
	MeshPtAdaptor, 3> Mesh_pt_kdtree;

typedef nanoflann::KDTreeSingleIndexAdaptor<
	nanoflann::L2_Simple_Adaptor<float, FrontPtAdaptor>,
	FrontPtAdaptor, 3> Front_pt_kdtree;

// Curvature Dependent Marching Triangles Polygonizer
class TrisPoly : public Polygonizer
{
public:
	TrisPoly(Implicit::Object& o):
		Polygonizer(o),
		m_mesh_adaptor(m_container),
		m_front_adaptor(m_container),
		m_mesh_tree(2, m_mesh_adaptor ,
				nanoflann::KDTreeSingleIndexAdaptorParams(10)),
		m_front_tree(2, m_front_adaptor,
				nanoflann::KDTreeSingleIndexAdaptorParams(10))

	{ }

protected:
	// Must have for polygonizer
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

	// Generate and set open angles in the front
	void actualizeAngles();

	// Uses front index value
	float computeOpenAngle(unsigned int i, const Front* f) const;

	// Gets the radius of curvature at a point
	// Maximum absolute curvature used to calculate
	float rocAtPt(const glm::vec3& v);


private:
	// Variables
	//Mesh m_mesh;

	PolyContainer m_container; // Contains all the data elements

	// See if these are necessary
	MeshPtAdaptor m_mesh_adaptor;
	FrontPtAdaptor m_front_adaptor;

	// Kd trees for finding closes point on the mesh or front
	Mesh_pt_kdtree m_mesh_tree;
	Front_pt_kdtree m_front_tree;
};





#endif//POLYTRIS_HPP
