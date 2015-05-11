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


#include <functional>
#include <list>
#include <vector>
#include <stack>
#include <cmath>
#include <chrono>
#include <unordered_map>
#include <utility>

#include <glm/glm.hpp>


// Tune this number
#define VERTEX_HASH_BUCKETS 10

class PolyContainer
{
public:

	typedef struct
	{
		unsigned int vert_index[3];
	} Face;

public:

	PolyContainer() :
		m_vertices(),
		m_normals(),
		m_vertRocs(),
		m_edges(),
		m_fronts(),
		m_faces(),
		m_vertex_index_map(VERTEX_HASH_BUCKETS, hashVector)
	{ }

	inline std::vector<glm::vec3> getVertices() { return m_vertices; }

	inline unsigned int verts() const { return m_vertices.size(); }
	inline unsigned int edges() const { return m_edges.size(); }
	inline unsigned int fronts() const { return m_fronts.size(); }
	inline unsigned int faces() const { return m_faces.size(); }

	// Vertex Handling
	inline const glm::vec3& getVertex(unsigned int index) const
	{ return m_vertices[index]; }


	inline void pushVertex(const glm::vec3 v)
	{
		m_vertex_index_map[v] = m_vertices.size();
		m_vertices.push_back(v);
	}

	inline unsigned int getVertexIndex(glm::vec3 v) const
	{ return m_vertex_index_map.at(v); }

	// Normal Handling

	inline const glm::vec3& getNormal(unsigned int index) const
	{ return m_normals[index]; }

	inline void pushNormal(const glm::vec3 n)
	{ m_normals.push_back(n); }

	// Face Handling

	inline const Face& getFace(unsigned int index) const
	{ return m_faces[index]; }

	inline void pushFace(Face f)
	{ m_faces.push_back(f); }


	// Front Handling

	inline Front* getFront() const
	{
		if (m_fronts.size() > 0) return m_fronts.back();
		else return NULL;
	}

	inline Front* getFront(unsigned int index) const
	{
		if (index < m_fronts.size()) return m_fronts[index];
		else return NULL;
	}

	inline void pushFront(Front* f)
	{ m_fronts.push_back(f); }

	// You should catch the pointer and delete it when done cause it isn't
	// being stored anymore
	Front* popFront()
	{
		Front* ret_front = m_fronts.back();
		m_fronts.pop_back();
		return ret_front;
	}

	// Roc handling
	inline const float getRoc(unsigned int index) const
	{ return m_vertRocs[index]; }

	inline void pushRoc(float roc)
	{ m_vertRocs.push_back(roc); }

private:
	static inline size_t hashVector(const glm::vec3& v)
	{
		return ((int)(v.x * 0x1459) ^ (int)(v.y * 0x713)) ^ (int)(v.z * 0x1c81);
	}


	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<float> m_vertRocs;
	std::vector<Edge> m_edges; // Don't think I need this
	std::vector<Front*> m_fronts;
	std::vector<Face> m_faces;

	// Tune the number of buckets
	std::unordered_map<glm::vec3, unsigned int, std::function<decltype(hashVector)> > m_vertex_index_map;
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
	FrontPtAdaptor(const PolyContainer& poly, const Front* f) :
		m_container(poly), m_front(f) { }

	inline unsigned int kdtree_get_point_count() const
	{ return m_front->size(); }

	inline float kdtree_distance(const float* p1,
			const unsigned int index, unsigned int size) const
	{
		return glm::length(glm::vec3(p1[0], p1[1], p1[2]) -
				m_container.getVertex(
					m_front->getVertex(index)));
	}

	inline float kdtree_get_pt(const unsigned int i, int dim) const
	{
		if (dim == 0)return
			m_container.getVertex(m_front->getVertex(i)).x;
		else if(dim == 1) return
			m_container.getVertex(m_front->getVertex(i)).y;
		else return m_container.getVertex(m_front->getVertex(i)).z;
	}

	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const {return false;}

private:
	const PolyContainer& m_container;
	const Front* m_front;
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
		m_mesh_tree(2, m_mesh_adaptor ,
				nanoflann::KDTreeSingleIndexAdaptorParams(10))
	{ }

protected:
	// Must have for polygonizer
	virtual Mesh polygonize();
private:
	//Methods

	// Generates a hexagon from a seed vertex
	// adds generated front to fronts
	Front* seedHexagon(const glm::vec3& start);

	Front* mergeFronts(Front* A, unsigned int a, Front* B, unsigned int b);
	void splitFronts(Front* F, Front* A, unsigned int a, Front* B, unsigned int b);

	// Only works on fronts with 3 or 4 vertices (a hole)
	void fill(Front* f);

	// Generate and set open angles in the front
	void actualizeAngles(Front* f);

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
//	FrontPtAdaptor m_front_adaptor;

	// Kd trees for finding closes point on the mesh or front
	Mesh_pt_kdtree m_mesh_tree;
//	Front_pt_kdtree m_front_tree;
};





#endif//POLYTRIS_HPP
