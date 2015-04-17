#ifndef DRAW_UTILS_HPP
#define DRAW_UTILS_HPP

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifdef DEBUG
#include <iostream>
#endif

void drawQuad(const glm::vec3& v1,
		const glm::vec3& v2,
		const glm::vec3& v3,
		const glm::vec3& v4,
		const glm::vec3& n1,
		const glm::vec3& n2,
		const glm::vec3& n3,
		const glm::vec3& n4);

void drawBox(const glm::vec3& max, const glm::vec3& min);
#endif//DRAW_UTILS_HPP
