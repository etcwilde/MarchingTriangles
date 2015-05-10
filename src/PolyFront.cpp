#include "PolyFront.hpp"

void Front::setVertex(unsigned int fi, unsigned int vi)
{
	m_vertex_index[(fi % m_vertex_index.size())] = vi;
	m_open_angles[(fi % m_vertex_index.size())] = 0;
	m_open_angles[(fi + 1 % m_vertex_index.size())] = 0;
	m_open_angles[(fi - 1 % m_vertex_index.size())] = 0;
	m_rocs[(fi % m_vertex_index.size())] = 0;
}


void Front::setOpeningAngle(unsigned int fi, float angle)
{
	m_open_angles[(fi % m_vertex_index.size())] = angle;
}

/*

void Front::setRadiusOfCurvature(unsigned int fi, float roc);

unsigned int Front::appendVertex(unsigned int vi);

unsigned int Front::prependVertex(unsigned int vi);

unsigned int Front::insertVertex(unsigned int fi, unsigned int vi);

void Front::removeVertex(unsigned int fi);
*/
