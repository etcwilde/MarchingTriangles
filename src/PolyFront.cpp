#include "PolyFront.hpp"

// TODO Check that going one past the end wraps around to front
unsigned int Front::nextVertex(unsigned int v)
{
	VertexIterator vertex = getIterator(v);
	VertexIterator nextVertex = vertex; nextVertex++;
	if (nextVertex == m_vertices.end()) nextVertex++;
	return nextVertex->m_index;
}

VertexIterator Front::nextIter(VertexIterator vertex)
{
	VertexIterator nextVertex = vertex; nextVertex++;
	if(nextVertex == m_vertices.end()) nextVertex++;
	return nextVertex;
}

unsigned int Front::prevVertex(unsigned int v)
{
	VertexIterator vertex = getIterator(v);
	VertexIterator prevVertex = vertex; prevVertex--;
	if (prevVertex == m_vertices.end()) prevVertex--;
	return prevVertex->m_index;
}

VertexIterator Front::prevIter(VertexIterator vertex)
{
	VertexIterator prevVertex = vertex; prevVertex--;
	if (prevVertex == m_vertices.end()) prevVertex--;
	return prevVertex;
}

VertexIterator Front::getIterator(unsigned int v)
{
	return m_VertIndexToFrontIterator[v];
}

void Front::insertVertex(unsigned int p, unsigned int v)
{
	VertexIterator iter;
	if (p)
	{
		if (m_VertIndexToFrontIterator.count(p) <= 0) return;
		iter = m_VertIndexToFrontIterator[p];
		iter = m_vertices.insert(iter, Front::Vertex(v));
	}
	else
	{
		m_vertices.push_back(Front::Vertex(v));
		iter = m_vertices.end();
		iter--;
	}
	m_VertIndexToFrontIterator[v] = iter;
}
