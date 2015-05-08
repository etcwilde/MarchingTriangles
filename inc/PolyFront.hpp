#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP
#include <vector>

//typedef struct FrontVertex;

class Front
{
public:
	Front();
	Front(const Front& f) : m_verts(f.m_verts) { }

	// Returns the index of the ith vertex
	inline unsigned int operator[](unsigned int i)
	{ return m_verts[i].v_index; }

	inline unsigned int verts() const { return m_verts.size(); }

	inline unsigned int getVertex(unsigned int index) const
	{ return m_verts[index].v_index; }

	inline void setOpenAngle(unsigned int vertex_index, float angle)
	{ m_verts[vertex_index].open_angle = angle; }

	inline float getOpenAngle(unsigned int vertex_index) const
	{ return m_verts[vertex_index].open_angle; }

	inline void setRoc(unsigned int vertex_index, float roc)
	{ m_verts[vertex_index].roc = roc; }

	inline float getRoc(unsigned int vertex_index) const
	{ return m_verts[vertex_index].roc; }

	// TODO: Put implementation in cpp file
	// Index Vertex: Index in TrisPolyVerts
	// neighbors: Index to verts in m_verts list
	void pushVertex(unsigned int vertex_index,
			unsigned int *neighbors = NULL,
			float open_angle = 0,
			float roc=1)
	{
		FrontVertex v;
		v.v_index = vertex_index;
		if (neighbors)
		{
			v.neighbors[0] = neighbors[0];
			v.neighbors[1] = neighbors[1];
		}
		v.open_angle = open_angle;
		v.roc = roc;
		m_verts.push_back(v);
	}


protected:

private:
	typedef struct FrontVertex
	{
		unsigned int v_index;
		unsigned int neighbors[2];
		// neighbors[0] is the left
		// neighbors[1] is the right
		float open_angle;
		float roc; // Radius of curvature
	} FrontVertex;

private:
	std::vector<FrontVertex> m_verts;

};


#endif//POLYFRONT_HPP


