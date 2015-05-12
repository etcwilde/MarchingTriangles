#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP
#include <vector>
#include <cmath>

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

	unsigned int getMinimalAngle() const;

	/**
	 * \brief Gets the vertex index from a front index
	 * \param fi Front Index, the index to get the vertex index from
	 */
	inline unsigned int getVertex(unsigned int fi) const
	{ return m_vertex_index[(fi % m_vertex_index.size())]; }

	/*
	inline unsigned int getVertexIndex(unsigned int vi) const
	{ return m_vertex_index.at(vi); }
	*/

	// Cannot be placed in a map
	// Due to how items can be inserted and removed from any location, it
	// isn't worth maintaining a map as the number of O(n) operations
	// skyrockets, whereas this is one O(n) operation
	unsigned int getVertexIndex(unsigned int vi) const;

	/**
	 * \brief Gets the vertex index of the vertex to the left
	 */
	inline unsigned int getLeft(unsigned int fi) const
	{
		std::cout << "fi : " << fi << '\n';
		if ((fi % m_vertex_index.size()) == 0)
			return m_vertex_index[m_vertex_index.size() - 1];
		return m_vertex_index[(fi - 1) % m_vertex_index.size()];
	}

	/**
	 * \brief Gets the vertex index of the vertex to the right
	 */
	inline unsigned int getRight(unsigned int fi) const
	{ return m_vertex_index[(fi + 1) % m_vertex_index.size()]; }

	/**
	 * \brief Gets the opening angle of a front vertex
	 */
	inline float getOpeningAngle(unsigned int fi) const
	{ return m_open_angles[fi % m_vertex_index.size()]; }

	/**
	 * \brief Gets the radius of curvature of a front vertex
	 *
	 * This is how far along the shape the curvature of this point has an
	 * effect
	 *
	 */
	inline float getRadiusOfCurvature(unsigned int fi) const
	{ return m_rocs[fi % m_vertex_index.size()]; }


	/**
	 * \brief Sets the vertex index of a front index
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param fi Front index
	 * \param vi vertex index
	 */
	void setVertex(unsigned int fi, unsigned int vi);

	inline void setOpeningAngle(unsigned int fi, float angle)
	{ m_open_angles[fi % m_vertex_index.size()] = angle; }

	inline void setRadiusOfCurvature(unsigned int fi, float roc)
	{ m_rocs[fi % m_vertex_index.size()] = roc; }


	/**
	 * \brief Inserts a vertex to the end
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param vi Vertex index of the new front vertex
	 * \return The front index of the new vertex
	 *
	 */
	unsigned int appendVertex(unsigned int vi);

	/**
	 * \brief Inserts a vertex at the front
	 *
	 * Note: opening angle and roc are initialized to 0
	 *
	 * \param vi Vertex index to be added
	 * \return The front index of the new vertex
	 */
	unsigned int prependVertex(unsigned int vi);

	/**
	 * \brief Inserts a new vertex at an arbitrary position
	 *
	 * Note: Opening angle and roc are initialized to 0
	 *
	 * \param fi Front index for the new vertex
	 * \param vi vertex index
	 */
	unsigned int insertVertex(unsigned int fi, unsigned int vi);

	/**
	 * \brief Removes a vertex at an arbitrary position
	 *
	 * Note: opening angle and roc are set to 0 for the neighbors
	 */
	void removeVertex(unsigned int fi);

	/**
	 * \brief Ensures that all the sizes of the datastructures are correct
	 */
	inline bool sanityCheck() const
	{ return (m_vertex_index.size() == m_open_angles.size() &&
			m_vertex_index.size() == m_rocs.size()); }

private:
	// The front vertices are not explicitly defined
	// They are implicit. A front index will index into one of these
	// vectors. That index for all vectors correspond to a given vertex
	std::vector<unsigned int> m_vertex_index;
	std::vector<float> m_open_angles;
	std::vector<float> m_rocs;
};


#endif//POLYFRONT_HPP


