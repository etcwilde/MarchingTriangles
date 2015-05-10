#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP
#include <vector>

class Front
{
public:
	Front() {}

	Front(const Front& f) : m_vertex_index(f.m_vertex_index),
		m_open_angles(f.m_open_angles),
		m_rocs(f.m_rocs) { }

	/**
	 * \brief Returns the number of vertices in the front
	 *
	 * \return Number of vertices in the front
	 */
	inline unsigned int size() const
	{ return m_vertex_index.size(); }
	// Translate a front index to a vertex index
	/**
	 * \brief Gets the vertex index from a front index
	 * \param fi Front Index, the index to get the vertex index from
	 */
	inline unsigned int getVertex(unsigned int fi) const
	{ return m_vertex_index[(fi % m_vertex_index.size())]; }

	inline unsigned int getLeft(unsigned int fi) const
	{ return m_vertex_index[(fi % m_vertex_index.size()) - 1]; }

	inline unsigned int getRight(unsigned int fi) const
	{ return m_vertex_index[(fi % m_vertex_index.size()) + 1]; }

	inline float getOpeningAngle(unsigned int fi) const
	{ return m_open_angles[(fi % m_vertex_index.size())]; }

	inline float getRadiusOfCurvature(unsigned int fi) const
	{ return m_rocs[(fi % m_vertex_index.size())]; }


	/**
	 * \brief Sets the vertex index of a front index
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param fi Front index
	 * \param vi vertex index
	 */
	inline void setVertex(unsigned int fi, unsigned int vi)
	{
		m_vertex_index[(fi % m_vertex_index.size())] = vi;
		m_open_angles[(fi % m_vertex_index.size())] = 0;
		m_open_angles[(fi + 1 % m_vertex_index.size())] = 0;
		m_open_angles[(fi - 1 % m_vertex_index.size())] = 0;
		m_rocs[(fi % m_vertex_index.size())] = 0;
	}

	inline void setOpeningAngle(unsigned int fi, float angle)
	{
		m_open_angles[(fi % m_vertex_index.size())] = angle;
	}

	inline void setRadiusOfCurvature(unsigned int fi, float roc)
	{
		m_rocs[(fi % m_vertex_index.size())] = roc;
	}


	/**
	 * \brief Inserts a vertex to the end
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param vi Vertex index of the new front vertex
	 * \return The front index of the new vertex
	 *
	 */
	inline unsigned int appendVertex(unsigned int vi)
	{
		m_open_angles[0] = 0;
		m_open_angles[m_vertex_index.size() - 1] = 0;
		m_vertex_index.push_back(vi);
		m_open_angles.push_back(0);
		m_rocs.push_back(0);
		return m_vertex_index.size() - 1;
	}

	/**
	 * \brief Inserts a vertex at the front
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param vi Vertex index to be added
	 * \return The front index of the new vertex
	 */
	inline unsigned int prependVertex(unsigned int vi)
	{
		m_open_angles[0] = 0;
		m_open_angles[m_vertex_index.size() - 1] = 0;
		m_vertex_index.insert(m_vertex_index.begin(), vi);
		m_open_angles.insert(m_open_angles.begin(), 0);
		m_rocs.insert(m_rocs.begin(), 0);
		return 0;
	}

	/**
	 * \brief Inserts a new vertex at an arbitrary position
	 *
	 * Note: Opening angle and roc are initialized to 0
	 *
	 * \param fi Front index for the new vertex
	 * \param vi vertex index
	 */
	inline unsigned int insertVertex(unsigned int fi, unsigned int vi)
	{
		fi = fi % m_vertex_index.size() + 1; // Don't go further than we have to
		m_open_angles[fi] = 0;
		m_open_angles[fi + 1] = 0;
		m_vertex_index.insert(m_vertex_index.begin() + fi, vi);
		m_open_angles.insert(m_open_angles.begin() + fi, 0);
		m_rocs.insert(m_rocs.begin() + fi, 0);
		return fi;
	}

	/**
	 * \brief Removes a vertex at an arbitrary position
	 *
	 * Note: opening angle and roc are set to 0 for the neighbors
	 */
	inline void removeVertex(unsigned int fi)
	{
		m_open_angles[fi + 1] = 0;
		m_open_angles[fi - 1] = 0;
		m_vertex_index.erase(m_vertex_index.begin() + fi);
		m_open_angles.erase(m_open_angles.begin() + fi);
		m_rocs.erase(m_rocs.begin() + fi);
	}

	inline bool sanityCheck() const
	{
		return (m_vertex_index.size() == m_open_angles.size() == m_rocs.size());
	}

	// Returns the index of the ith vertex
	/*
	inline unsigned int operator[](unsigned int i)
	{ return m_verts[i].v_index; }

	inline unsigned int verts() const { return m_verts.size(); }

	inline unsigned int getLeft(unsigned int i) const
	{
		return m_verts[m_verts[i].neighbors[0]].v_index;
	}

	inline unsigned int getRight(unsigned int i) const
	{
		return m_verts[m_verts[i].neighbors[1]].v_index;
	}

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
	*/


	// If we keep the vertex container ordered, we don't need to keep track
	// of our neighbors
	//
	// The right-hand vertex will always be to the right, and the left will
	// always be on the left in the buffer


	// TODO: Put implementation in cpp file
	// Index Vertex: Index in TrisPolyVerts
	// neighbors: Index to verts in m_verts list
	// Circularly-linked doubly-linked list implemented in an array-style

	/*
	void pushVertex(unsigned int vertex_index)
	{
		unsigned int my_index = m_verts.size();
		unsigned int first_index = 0;
		unsigned int last_index = m_verts.size() - 1;

		FrontVertex f;
		f.v_index = vertex_index;
		f.open_angle = 0;
		f.roc = 1;

		if (m_verts.size() > 0)
		{
			FrontVertex *first, *last;
			first = &m_verts[first_index];
			last = &m_verts[last_index];

			f.neighbors[0] = last_index;
			f.neighbors[1] = first_index;

			first->neighbors[0] = my_index;
			last->neighbors[1] = my_index;
		}
		else f.neighbors[0] = f.neighbors[1] = 0;
		m_verts.push_back(f);
	}

	// Removes the last vertex
	// Updates the neighbor links
	// TODO: Check that this actually works
	void popVertex()
	{
		if (m_verts.size() ==  0) return;
		else if (m_verts.size() == 1) m_verts.pop_back();
		unsigned int my_index = m_verts.size() - 1;
		unsigned int first_index = 0;
		unsigned int last_index = m_verts.size() - 2;

		m_verts[last_index].neighbors[0] = first_index;
		m_verts[first_index].neighbors[1] = last_index;

		m_verts.pop_back();
	}
	*/

protected:

private:

private:
	std::vector<unsigned int> m_vertex_index;
	std::vector<float> m_open_angles;
	std::vector<float> m_rocs;
};


#endif//POLYFRONT_HPP


