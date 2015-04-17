
#include "DrawUtils.hpp"

void drawQuad(const glm::vec3& v1,
		const glm::vec3& v2,
		const glm::vec3& v3,
		const glm::vec3& v4,
		const glm::vec3& n1,
		const glm::vec3& n2,
		const glm::vec3& n3,
		const glm::vec3& n4)
{
	glBegin(GL_QUADS);

	glNormal3f(n1.x, n1.y, n1.z);
	glVertex3f(v1.x, v1.y, v1.z);

	glNormal3f(n2.x, n2.y, n2.z);
	glVertex3f(v2.x, v2.y, v2.z);

	glNormal3f(n3.x, n3.y, n3.z);
	glVertex3f(v3.x, v3.y, v3.z);

	glNormal3f(n4.x, n4.y, n4.z);
	glVertex3f(v4.x, v4.y, v4.z);

	glEnd();
}

void drawBox(const glm::vec3& max, const glm::vec3& min)
{
	const glm::vec3 xa = glm::vec3(1, 0, 0);
	const glm::vec3 ya = glm::vec3(0, 1, 0);
	const glm::vec3 za = glm::vec3(0, 0, 1);

	glm::vec3 v[8];


	v[0] = glm::vec3( min.x, min.y, min.z);
	v[1] = glm::vec3( max.x, min.y, min.z);
	v[2] = glm::vec3( min.x, max.y, min.z);
	v[3] = glm::vec3( max.x, max.y, min.z);
	v[4] = glm::vec3( min.x, min.y, max.z);
	v[5] = glm::vec3( max.x, min.y, max.z);
	v[6] = glm::vec3( min.x, max.y, max.z);
	v[7] = glm::vec3( max.x, max.y, max.z);


	drawQuad(v[0], v[2], v[3], v[1], -za, -za, -za, -za);
	drawQuad(v[5], v[7], v[6], v[4], za, za, za, za);
	drawQuad(v[0], v[1], v[5], v[4], -ya, -ya, -ya, -ya);
	drawQuad(v[2], v[6], v[7], v[3], ya, ya, ya, ya);
	drawQuad(v[0], v[4], v[6], v[2], -xa, -xa, -xa, -xa);
	drawQuad(v[3], v[7], v[5], v[1], xa, xa, xa, xa);
}
