#include "ImplicitObject.hpp"
using namespace Implicit;

bool Object::touches(glm::vec3 pt)
{
	return (f_equ(getFieldValue(pt), 0, 0.8f) && contains(pt, 0.8f));
}

// Numerical_differentiation on wikipedia
void Object::getDeltas(float& h_x, float& h_y, float& h_z, const glm::vec3& pt,
		float eps)
{
	float x = std::abs(pt.x);
	float y = std::abs(pt.y);
	float z = std::abs(pt.z);
	h_x = eps * std::max(x, 1.f);
	h_y = eps * std::max(y, 1.f);
	h_z = eps * std::max(z, 1.f);
	volatile register float tmp_x = x + h_x;
	volatile register float tmp_y = y + h_y;
	volatile register float tmp_z = z + h_z;
	h_x = tmp_x - x;
	h_y = tmp_y - y;
	h_z = tmp_z - z;
}

glm::vec3 Object::gradient(glm::vec3 pt)
{

	// Gradient = [f'x(x, y, z), f'y(x, y, z), f'z(x, y, z)]

	float h_x, h_y, h_z;
	getDeltas(h_x, h_y, h_z, pt, NUMERICAL_EPSILON); // Well see
	glm::vec3 dx(h_x, 0.f, 0.f);
	glm::vec3 dy(0.f, h_y, 0.f);
	glm::vec3 dz(0.f, 0.f, h_z);

	std::cout << "Detas: "
		<< h_x << ", "
		<< h_y << ", "
		<< h_z << "\n";






	float inv_2hx = 0.5f/h_x;
	float inv_2hy = 0.5f/h_y;
	float inv_2hz = 0.5f/h_z;

	float vxp = getFieldValue(pt + dx);
	float vxm = getFieldValue(pt - dx);
	float vyp = getFieldValue(pt + dy);
	float vym = getFieldValue(pt - dy);
	float vzp = getFieldValue(pt + dz);
	float vzm = getFieldValue(pt - dz);
	float grad_x = inv_2hx * (vxp - vxm);
	float grad_y = inv_2hy * (vyp - vym);
	float grad_z = inv_2hz * (vzp - vzm);

	return glm::vec3 (grad_x, grad_y, grad_z);
}


glm::mat3 Object::hessian(glm::vec3 point)
{
	float h_x, h_y, h_z;
	getDeltas(h_x, h_y, h_z, point, NUMERICAL_EPSILON);

	glm::vec3 d_x(h_x, 0.f, 0.f);
	glm::vec3 d_y(0.f, h_y, 0.f);
	glm::vec3 d_z(0.f, 0.f, h_z);

	glm::vec3 gxp = gradient(point + d_x);
	glm::vec3 gxm = gradient(point - d_x);
	glm::vec3 gyp = gradient(point + d_y);
	glm::vec3 gym = gradient(point - d_y);
	glm::vec3 gzp = gradient(point + d_z);
	glm::vec3 gzm = gradient(point - d_z);

	float inv_2hx = 0.5f/h_x;
	float inv_2hy = 0.5f/h_y;
	float inv_2hz = 0.5f/h_z;
	float h_xx = inv_2hx * (gxp.x - gxm.x);
	float h_yy = inv_2hy * (gyp.y - gym.y);
	float h_zz = inv_2hz * (gzp.z - gzm.z);
	float h_xy = 0.5f*(inv_2hx*(gxp.y - gxm.y) + inv_2hy*(gyp.x - gyp.x));
	float h_yz = 0.5f*(inv_2hy*(gyp.z - gym.z) + inv_2hz*(gzp.y - gzp.y));
	float h_xz = 0.5f*(inv_2hz*(gzp.x - gzm.x) + inv_2hx*(gxp.z - gxp.z));

	glm::vec3 col0(h_xx, h_xy, h_xz);
	glm::vec3 col1(h_xy, h_yy, h_xy);
	glm::vec3 col2(h_xz, h_yz, h_zz);
	glm::mat3 H(col0, col1, col2);
}


void Object::curvature(const glm::vec3& point, float& k1, float& k2)
{
	glm::vec3 grad = gradient(point);
	//glm::mat3 H = 
}

