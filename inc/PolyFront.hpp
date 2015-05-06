#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP

#include <list>
#include <map>

class Front
{
public:
	// Data Structures
	/*
	 * Front Vertex Manipulation
	 */
	struct Vertex
	{
		Vertex(unsigned int index) :
			m_index(index),
			m_active(true)
		{ }
		unsigned int m_index;
		bool m_active;
		float m_openAngle;
		unsigned int m_triangleIndex;

		bool operator < (const Vertex& v) const
		{
			return m_openAngle < v.m_openAngle;
		}
	};

public:
	// Returns index of next vertex
	unsigned int nextVertex(unsigned int v);
	std::list<Vertex>::iterator nextIter(std::list<Vertex>::iterator vertex);

	// Returns the index of the previous vertex
	unsigned int prevVertex(unsigned int v);
	std::list<Vertex>::iterator prevIter(std::list<Vertex>::iterator vertex);

	// Get the iterator from a vertex index
	std::list<Vertex>::iterator getIterator(unsigned int v);

	// Insert a new vertex v immediately after vertex p
	void insertVertex(unsigned int p, unsigned int v);
protected:
private:

private:
	//Variables
	std::list<Vertex> m_vertices;
	std::map<unsigned int, std::list<Vertex>::iterator> m_VertIndexToFrontIterator;
};

typedef std::list<Front::Vertex>::iterator VertexIterator;

#endif//POLYFRONT_HPP


