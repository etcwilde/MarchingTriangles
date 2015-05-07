#ifndef POLYFRONT_HPP
#define POLYFRONT_HPP
#include <vector>

typedef struct FrontVertex;

class Front
{
public:
	Front();
	Front(const Front& f) : m_verts(f.m_verts) { }

	// Returns the index of the ith vertex
	inline unsigned int operator[](unsigned int i)
	{ return m_verts[i].v_index; }

protected:

private:
	typedef struct
	{
		unsigned int v_index;
		FrontVertex*[2] neighbors;
	} FrontVertex;

private:
	std::vector<FrontVertex> m_verts;

};


#endif//POLYFRONT_HPP


