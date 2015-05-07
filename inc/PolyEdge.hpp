#ifndef POLYEDGE_HPP
#define POLYEDGE_HPP

class Edge
{
public:
	Edge(unsigned int v1, unsigned int v2) : m_vertIndex[0](v1), m_vertIndex[1](v1) { }
	// index: 0 or 1
	unsigned int get(unsigned char index) const { return m_vertIndex[index]; }
private:
	unsigned int m_vertIndex[2];
};

#endif//POLYEDGE_HPP
