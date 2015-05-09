#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP
#include <vector>

//typedef struct FrontVertex;

class Front
{
public:
	Front() {}
	Front(const Front& f) : m_verts(f.m_verts) { }

	// Returns the index of the ith vertex
	inline unsigned int operator[](unsigned int i)
	{ return m_verts[i].v_index; }

	inline unsigned int verts() const { return m_verts.size(); }

	inline unsigned int getLeft(unsigned int i) const
	{
		return m_verts[m_verts[i].neighbors[0]].v_index;
	}

	/*
	inline unsigned int setNeighbor1Index(unsigned int i, unsigned int ni) const
	{
		m_verts[i].neighbors[0] = ni;
	}
	*/

	inline unsigned int getRight(unsigned int i) const
	{
		return m_verts[m_verts[i].neighbors[1]].v_index;
	}

	/*
	inline unsigned int setNeighbor2Index(unsigned int i unsigned int ni) const
	{
		m_verts[i].neighbors[1] = ni;
	}
	*/

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
	// Circularly-linked doubly-linked list implemented in an array-style
	void pushVertex(unsigned int vertex_index,
			float open_angle = 0,
			float roc = 1)
	{
		unsigned int my_index = m_verts.size();
		unsigned int first_index = 0;
		unsigned int last_index = m_verts.size() - 1;

		FrontVertex f;
		f.v_index = vertex_index;
		f.open_angle = open_angle;
		f.roc = roc;
#ifdef DEBUG
		std::cout << "Building Vertex" << vertex_index << ": " << '\n';
#endif

		if (m_verts.size() > 0)
		{
			FrontVertex *first, *last;
			first = &m_verts[first_index];
			last = &m_verts[last_index];

			f.neighbors[0] = last_index;
			f.neighbors[1] = first_index;

			first->neighbors[0] = my_index;
			last->neighbors[1] = my_index;
			// HAHAHAHAHA 
			// In case you are wondering, this is just pushing a
			// vertex onto the back
		}
		else
		{
			// There are currently no vertices in the list
			// Just insert ourselves and reference us
			f.neighbors[0] = f.neighbors[1] = 0;

		}

		m_verts.push_back(f);
#ifdef DEBUG
		for (unsigned int i = 0; i < m_verts.size(); ++i)
		{
			std::cout << i << '[' << m_verts[i].v_index << "] " << " : " << m_verts[i].neighbors[0]
			<< ", " << m_verts[i].neighbors[1] << '\n';
		}
#endif
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


