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

	// If we keep the vertex container ordered, we don't need to keep track
	// of our neighbors
	//
	// The right-hand vertex will always be to the right, and the left will
	// always be on the left in the buffer


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
	inline void setVertex(unsigned int fi, unsigned int vi);

	inline void setOpeningAngle(unsigned int fi, float angle);

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



protected:

private:

private:
	std::vector<unsigned int> m_vertex_index;
	std::vector<float> m_open_angles;
	std::vector<float> m_rocs;
};


#endif//POLYFRONT_HPP


