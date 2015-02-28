#include "ImplicitObject.hpp"
using namespace Implicit;

glm::vec3 Object::gradient(glm::vec3 pt)
{
	glm::vec3 sample_1;
	glm::vec3 sample_2;
	glm::vec3 sample_3;
	glm::vec3 sample_4;
	glm::vec3 sample_5;
	glm::vec3 sample_6;


	return glm::vec3 (0, 0, 0);
}

float Object::maxCurvature(glm::vec3 pt)
{
	float x_curve;
	float y_curve;
	float z_curve;

	return x_curve < y_curve ? (y_curve < z_curve ? z_curve : y_curve ) :
		x_curve;
}

float Object::derivative(glm::vec3 pt)
{
	// getFieldValue
	return 0.f;
}
