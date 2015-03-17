/*
 * ImplicitObject
 *
 * File: 	ImplicitObject.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 18 2015
 */

#include "ImplicitObject.hpp"

using namespace Implicit;

Object::Object():
	m_iso(0.5f),
	m_center()
{ }

Object::Object(float iso) :
	m_iso(iso),
	m_center()
{ }

Object::Object(glm::vec3 center, float iso) :
	m_iso(iso),
	m_center(center)
{ }

void Object::SetIso(float iso)
{
	m_iso = iso;
}

glm::vec3 Object::Project(glm::vec3 p)
{
	return project(p);
}

glm::vec3 Object::GetStartVertex()
{
	return Project(m_center);
}

void Object::Curvature(const glm::vec3& pt, float& k1, float& k2)
{
	glm::vec3 grad = Normal(pt);
	glm::mat3 H = hessian(pt);
	glm::mat3 C = surfaceCurvature(H);
	float nfsqr = glm::dot(grad, grad);

	float gaussian = glm::dot(grad, (grad * C)) / (nfsqr*nfsqr + FLT_EPSILON);
	float mean = (glm::dot(grad, (grad * H)) - nfsqr *
			(H[0][0] + H[1][1] + H[2][2]))
			/ (2.f * nfsqr + FLT_EPSILON);
	float det = std::sqrt(abs(mean * mean - gaussian));
	k1 = mean + det;
	k2 = mean - det;
#ifdef DEBUG
	std::cout << "Gaussian: " << gaussian << '\t' << "Mean: " << mean
		<< '\n' << "Determinant: " << det << '\n'
		<< "K1: " << k1 << '\t' << "K2: " << k2 << '\n';
#endif
}


void Object::getDeltas(float& dx, float& dy, float& dz, const glm::vec3& pt,
		float eps)
{
	float x = std::abs(pt.x);
	float y = std::abs(pt.y);
	float z = std::abs(pt.z);

	dx = eps * std::max(x, 1.f);
	dy = eps * std::max(y, 1.f);
	dz = eps * std::max(z, 1.f);
	volatile float tmpx = x + dx;
	volatile float tmpy = y + dy;
	volatile float tmpz = z + dz;
	dx = tmpx - x;
	dy = tmpy - y;
	dz = tmpz - z;
}

glm::mat3 Object::hessian(const glm::vec3& pt)
{
	static const float EPSILON = FLT_EPSILON;
	float hx, hy, hz;
	getDeltas(hx, hy, hz, pt, EPSILON);

	glm::vec3 dx(hx, 0, 0);
	glm::vec3 dy(0, hy, 0);
	glm::vec3 dz(0, 0, hz);

	glm::vec3 gxp = Normal(pt + dx);
	glm::vec3 gxm = Normal(pt - dx);
	glm::vec3 gyp = Normal(pt + dy);
	glm::vec3 gym = Normal(pt - dy);
	glm::vec3 gzp = Normal(pt + dz);
	glm::vec3 gzm = Normal(pt - dz);


	float inv_2hx = 0.5f/hx;
	float inv_2hy = 0.5f/hy;
	float inv_2hz = 0.5f/hz;

	float hxx = inv_2hx * (gxp.x - gxm.x);
	float hyy = inv_2hy * (gyp.y - gym.y);
	float hzz = inv_2hz * (gzp.z - gzm.z);
	float hxy = 0.5f*(inv_2hx*(gxp.y - gxm.y) + inv_2hy*(gyp.x - gyp.x));
	float hyz = 0.5f*(inv_2hy*(gyp.z - gym.z) + inv_2hz*(gzp.y - gzp.y));
	float hxz = 0.5f*(inv_2hz*(gzp.x - gzm.x) + inv_2hx*(gxp.z - gxp.z));

	glm::vec3 col0(hxx, hxy, hxz);
	glm::vec3 col1(hxy, hyy, hxy);
	glm::vec3 col2(hxz, hyz, hzz);
	glm::mat3 H(col0, col1, col2);
	return H;
}

glm::mat3 Object::surfaceCurvature(const glm::mat3& m)
{
	float Mxx = m[0][0];
	float Myy = m[1][1];
	float Mzz = m[2][2];
	float Mxy = m[0][1];
	float Mxz = m[0][2];
	float Myz = m[1][2];
	glm::mat3 C;
	C[0][0] = Myy * Mzz - Myz * Myz;
	C[1][1] = Mxx * Mzz - Mxz * Mxz;
	C[2][2] = Mxx * Myy - Mxy * Mxy;
	C[1][0] = Mxy * Mxz - Mxy * Mzz;
	C[2][0] = Mxy * Myz - Myy * Mxz;
	C[2][1] = Mxy * Mxz - Mxx * Myz;
	C[0][1] = m[1][0];
	C[0][2] = m[2][0];
	C[1][2] = m[2][1];
	return C;
}

float Object::findRoot(glm::vec3 point, glm::vec3 direction)
{
	direction = glm::normalize(direction);
	float ret_val;
	register float xi;
	register float xi1 = 0;
	register float xi2 = 1;
#ifdef DEBUG
	unsigned int iteration = 0;
#endif
	for (unsigned int i = 0; i < FIND_ROOT_ITERS; ++i)
	{
		register float fxi1 = Evaluate(point + (direction * xi1));
		register float fxi2 = Evaluate(point + (direction * xi2));
		xi = xi1 - fxi1 * ((xi1 - xi2)/(fxi1 - fxi2));
		if (fxi1 == fxi2)
		{
			ret_val = xi1;
#ifdef DEBUG
			iteration = i;
#endif
			break;
		}
		xi2 = xi1; xi1 = xi;
	}
#ifdef DEBUG
	std::cout << "Iterations: " << iteration << '\n';
#endif
	return ret_val;
}

void Object::getTangentSpace(const glm::vec3& N, glm::vec3& T, glm::vec3& B)
	const
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}

glm::vec3 Object::project(glm::vec3 pt)
{
	// the point + some distance along the gradient
	// Gives us the point on the surface
	return pt + (Normal(pt) * findRoot(pt, Normal(pt)));
}

