#include "Triangle.hpp"

std::list<glm::vec3> Triangle::get_vertices()
{
	std::list<glm::vec3> verts;
	verts.push_back(vertex_3);
	verts.push_back(vertex_2);
	verts.push_back(vertex_1);

	return verts;
}

#include <GL/gl.h>
void Triangle::Draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);
	glVertex3f(vertex_2.x, vertex_2.y, vertex_2.z);
	glVertex3f(vertex_3.x, vertex_3.y, vertex_3.z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);
	glVertex3f(vertex_2.x, vertex_2.y, vertex_2.z);
	glVertex3f(vertex_3.x, vertex_3.y, vertex_3.z);
	glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);
	glEnd();
}
