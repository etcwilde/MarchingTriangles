#include "PolyFront.hpp"

unsigned int Front::getMinimalAngle() const
{
	float minimal_angle = 2 * M_PI; // 360 degrees
	unsigned int minimal_index = 0;
	// Think about pipeline optimization here
	for (unsigned int i = 0; i < m_open_angles.size(); ++i)
	{
		if (m_open_angles[i] < minimal_angle)
		{
			minimal_angle = m_open_angles[i];
			minimal_index = i;
		}
	}
	return minimal_index;
}

unsigned int Front::getVertexIndex(unsigned int vi) const
{
	for (unsigned int fi = 0; fi < m_vertex_index.size(); ++fi)
		if (m_vertex_index[fi] == vi) return fi;
	// There was an error -- This should throw an error instead
	return 0;
}

void Front::setVertex(unsigned int fi, unsigned int vi)
{
	if (fi < m_vertex_index.size())
	{
		m_vertex_index[(fi % m_vertex_index.size())] = vi;
		m_open_angles[(fi % m_vertex_index.size())] = 0;
		m_open_angles[(fi + 1 % m_vertex_index.size())] = 0;
		m_open_angles[(fi - 1 % m_vertex_index.size())] = 0;
		m_rocs[(fi % m_vertex_index.size())] = 0;
	}
}

unsigned int Front::appendVertex(unsigned int vi)
{
	if (m_vertex_index.size() > 0)
	{
		m_open_angles[0] = 0;
		m_open_angles[m_vertex_index.size() - 1] = 0;
	}
	m_vertex_index.push_back(vi);
	m_open_angles.push_back(0);
	m_rocs.push_back(0);
	return m_vertex_index.size() - 1;
}

unsigned int Front::prependVertex(unsigned int vi)
{
	if (m_vertex_index.size() > 0)
	{
		m_open_angles[0] = 0;
		m_open_angles[m_vertex_index.size() - 1] = 0;
	}
	m_vertex_index.insert(m_vertex_index.begin(), vi);
	m_open_angles.insert(m_open_angles.begin(), 0);
	m_rocs.insert(m_rocs.begin(), 0);
	return 0;
}

unsigned int Front::insertVertex(unsigned int fi, unsigned int vi)
{
	fi = fi % m_vertex_index.size() + 1;
	m_open_angles[fi] = 0;
	m_open_angles[fi + 1] = 0;
	m_vertex_index.insert(m_vertex_index.begin() + fi, vi);
	m_open_angles.insert(m_open_angles.begin() + fi, 0);
	m_rocs.insert(m_rocs.begin() + fi, 0);
	return fi;

}

void Front::removeVertex(unsigned int fi)
{
	unsigned int left_i;
	if ((fi % m_vertex_index.size()) == 0)
		left_i = m_vertex_index.size() - 1;
	else left_i = fi - 1;


	if (m_vertex_index.size() <= 0) return;
	m_open_angles[fi + 1] = 0;
	m_open_angles[left_i] = 0;
	m_vertex_index.erase(m_vertex_index.begin() + fi);
	m_open_angles.erase(m_open_angles.begin() + fi);
	m_rocs.erase(m_rocs.begin() + fi);
}
