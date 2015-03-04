#include "Polygonizer.hpp"

Polygonizer::Polygonizer(Implicit::Object* obj) :
	m_iso(0.5),
	m_object(obj),
	m_tolerance(1),
	m_scale(1),
	m_triangles(),
	m_seeds()
{}

Polygonizer::Polygonizer(Implicit::Object* obj, float iso) :
	m_iso(iso),
	m_object(obj),
	m_tolerance(1),
	m_scale(1),
	m_triangles(),
	m_seeds()
{}

Polygonizer::Polygonizer(Implicit::Object* obj, float iso, float scale) :
	m_iso(iso),
	m_object(obj),
	m_tolerance(1),
	m_scale(scale),
	m_triangles(),
	m_seeds()
{}

list<Triangle>Polygonizer::polygonize(list<glm::vec3> seed_points)
{
	m_seeds = seed_points;
	float iso = m_object->getFieldValue(*(seed_points.begin()));
	std::cout << "iso Value: " << iso << '\n';

	glm::vec3 test_pt(3, 1, 1);

	std::cout << "test pt: "
		<< test_pt.x << ", "
		<< test_pt.y << ", "
		<< test_pt.z << '\n';

	glm::vec3 pt = project(test_pt, 1);

	std::cout << "iso value 2: " << m_object->getFieldValue(pt) << '\n';
	return m_triangles;
}

list<Triangle> Polygonizer::polygonize()
{
	// Must find seed points
	return m_triangles;
}


// Protected Methods

glm::vec3 Polygonizer::project(glm::vec3 point, float tol)
{
	/*glm::vec3 ret_vec;
	glm::vec3 next_step;
	glm::vec3 this_step;
	glm::vec3 grad;
	float f;

	this_step = point;


	std::cout << "Newton Raphson\n";
	for (unsigned int i = 0; i < 10; ++i)
	{
		f = m_object->getFieldValue(this_step);
		grad = gradient(this_step);
		next_step.x = this_step.x - (f/grad.x);
		next_step.y = this_step.y - (f/grad.y);
		next_step.z = this_step.z - (f/grad.z);
		this_step = next_step;
	}
	std::cout << "Final Variables:\n"
		<< "Field Value: " << f << '\n'
		<< "Gradient : "
		<< grad.x << ", "
		<< grad.y << ", "
		<< grad.z << '\n'
		<< "Point: "
		<< this_step.x << ", "
		<< this_step.y << ", "
		<< this_step.z << '\n';

	return this_step; */

	float r = glm::length(point);
	float dv = derivative(point);
	glm::vec3 grad = gradient(point);
	return r + (dv * grad) / (grad * grad);
}

glm::vec3 Polygonizer::gradient(const glm::vec3& pt)
{
	//TODO find a good number for this
	static const float eps = 0.001f;
	float hx, hy, hz;
	getDeltas(hx, hy, hz, pt, eps);

	glm::vec3 dx(hx, 0, 0);
	glm::vec3 dy(0, hy, 0);
	glm::vec3 dz(0, 0, hz);

	std::cout << "Gradient Deltas: "
		<< hx << ", "
		<< hy << ", "
		<< hz << '\n';

	float inv_2hx = 0.5/hx;
	float inv_2hy = 0.5/hy;
	float inv_2hz = 0.5/hz;
	float vxp = m_object->getFieldValue(pt + dx);
	float vxm = m_object->getFieldValue(pt - dx);
	float vyp = m_object->getFieldValue(pt + dy);
	float vym = m_object->getFieldValue(pt - dy);
	float vzp = m_object->getFieldValue(pt + dz);
	float vzm = m_object->getFieldValue(pt - dz);
	float grad_x = inv_2hx * (vxp - vxm);
	float grad_y = inv_2hy * (vyp - vym);
	float grad_z = inv_2hz * (vzp - vzm);

	return glm::vec3 (grad_x, grad_y, grad_z);
}

glm::mat3 Polygonizer::hessian(const glm::vec3& pt)
{
	//TODO find a good number for this
	static const float eps = 0.001f;

	float hx, hy, hz;
	getDeltas(hx, hy, hz, pt, eps);
	std::cout << "Hessian Deltas: "
		<< hx << ", "
		<< hy << ", "
		<< hz << '\n';

	glm::vec3 dx(hx, 0, 0);
	glm::vec3 dy(0, hy, 0);
	glm::vec3 dz(0, 0, hz);

	glm::vec3 gxp = gradient(pt + dx);
	glm::vec3 gxm = gradient(pt - dx);
	glm::vec3 gyp = gradient(pt + dy);
	glm::vec3 gym = gradient(pt - dy);
	glm::vec3 gzp = gradient(pt + dz);
	glm::vec3 gzm = gradient(pt - dz);
	float inv_2hx = 0.5/hx;
	float inv_2hy = 0.5/hy;
	float inv_2hz = 0.5/hz;
	float hxx = inv_2hx*(gxp.x - gxm.x);
	float hyy = inv_2hy*(gyp.y - gym.y);
	float hzz = inv_2hz*(gzp.z - gzm.z);
	float hxy = 0.5*(inv_2hx*(gxp.y- gxm.y) + inv_2hy*(gyp.x- gym.x));
	float hyz = 0.5*(inv_2hy*(gyp.z- gym.z) + inv_2hz*(gzp.y- gzm.y));
	float hxz = 0.5*(inv_2hz*(gzp.x- gzm.x) + inv_2hx*(gxp.z- gxm.z));

	glm::vec3 col0(hxx, hxy, hxz);
	glm::vec3 col1(hxy, hyy, hxy);
	glm::vec3 col2(hxz, hyz, hzz);

	return glm::mat3(col0, col1, col2);
}

void Polygonizer::getDeltas(float &hx, float &hy, float &hz, const glm::vec3& pt, float eps)
{
	float x = std::abs(pt.x);
	float y = std::abs(pt.y);
	float z = std::abs(pt.z);
	hx = eps * std::max(x, 1.f);
	hy = eps * std::max(y, 1.f);
	hz = eps * std::max(z, 1.f);

	volatile float tmp_x = x + hx;
	volatile float tmp_y = y + hy;
	volatile float tmp_z = z + hz;

	hx = tmp_x + x;
	hy = tmp_y + y;
	hz = tmp_z + z;
}

void Polygonizer::computeTangent(const glm::vec3& N, glm::vec3& T, glm::vec3& B)
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}

void Polygonizer::curvature(const glm::vec3& p, float& k1, float& k2)
{
	glm::vec3 grad = gradient(p);
	glm::mat3 H = hessian(p);
	glm::mat3 Ha = adjoint(H);

	float gradsqr = glm::dot(grad, grad);
	float gaussian = (glm::dot(grad, grad * Ha)) / (gradsqr *gradsqr);
	float mean = (glm::dot(grad, grad*H)-gradsqr*(H[0][0]+H[1][1]+H[2][2]))
		/ (2.f * gradsqr*glm::length(grad));
	double det = sqrt(abs(mean * mean - gaussian));
	k1 = mean + det;
	k2 = mean - det;
}

float Polygonizer::derivative(glm::vec3 pt)
{
	// Small delta
	
	static const float delta = 0.0001f;
	// Move a tiny bit along gradient
	glm::vec3 grad = gradient(pt);
	glm::vec3 test = delta * grad + pt;

	float x1, x2;
	float y1, y2;
	x1 = glm::length(pt);
	x2 = glm::length(test);
	y1 = m_object->getFieldValue(pt);
	y2 = m_object->getFieldValue(test);

	return (y1 - y2) / (x1 - x2);

}

glm::mat3 Polygonizer::adjoint(const glm::mat3& F)
{
	float fxx = F[0][0];
	float fyy = F[1][1];
	float fzz = F[2][2];
	float fxy = F[0][1];
	float fxz = F[0][2];
	float fyz = F[1][2];

	glm::mat3 A;
	A[0][0] = fyy * fzz - fyz * fyz;
	A[1][1] = fxx * fzz - fxz * fxz;
	A[2][2] = fxx * fyy - fxy * fxy;
	A[1][0] = fyz * fxz - fxy * fzz;
	A[2][0] = fxy * fyz - fyy * fxz;
	A[2][1] = fxy * fxz - fxx * fyz;
	A[0][2] = F[1][0];
	A[0][2] = F[2][0];
	A[1][2] = F[2][1];
	return A;
}

