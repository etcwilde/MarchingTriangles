#include "ImplicitJack.hpp"

using namespace glm;
using namespace Implicit;

Jack::Jack(float (*fieldFunc)(float)):
	ImplicitModel(fieldFunc)
{ }

Jack::Jack(float (*fieldFunc)(float), float coeff) :
	ImplicitModel(fieldFunc, coeff)
{ }

float Jack::getFieldValue(vec3 pt)
{
	m_coeff * m_fieldFunc(getDistanceSq(pt) / 4);
}

float Jack::getDistanceSq(vec3 pt)
{
	float x, xs;
	float y, ys;
	float z, zs;
	x = pt.x;
	y = pt.y;
	z = pt.z;

	xs = x * x;
	ys = y * y;
	zs = z * z;

	float chunk_1 = ((xs / 9) + (4 * ys) + (4 * zs));
	float chunk_2 = ((4 * xs) + (ys / 9) + (4 * zs));
	float chunk_3 = ((4 * xs) + (4 * ys) + (zs / 9));

	float chunk_4 = (((4*x / 3) - 4) * ((4*x / 3) - 4) + 16*ys/9 + 16*zs/9);
	float chunk_5 = (((4*x / 3) + 4) * ((4*x / 3) + 4) - 16*ys/9 + 16*zs/9);

	float chunk_6 = (((4*y / 3) - 4) * ((4*y / 3) - 4) + 16*xs/9 + 16*zs/9);
	float chunk_7 = (((4*y / 3) + 4) * ((4*y / 3) + 4) - 16*xs/9 + 16*zs/9);

	float chunk_1_4 = chunk_1 * chunk_1 * chunk_1 * chunk_1;
	float chunk_2_4 = chunk_2 * chunk_2 * chunk_2 * chunk_2;
	float chunk_3_4 = chunk_3 * chunk_3 * chunk_3 * chunk_3;
	float chunk_4_4 = chunk_4 * chunk_4 * chunk_4 * chunk_4;
	float chunk_5_4 = chunk_5 * chunk_5 * chunk_5 * chunk_5;
	float chunk_6_4 = chunk_6 * chunk_6 * chunk_6 * chunk_6;
	float chunk_7_4 = chunk_7 * chunk_7 * chunk_7 * chunk_7;

	float block_1 = std::sqrt(std::sqrt(chunk_1_4 + chunk_2_4 + chunk_3_4 + chunk_4_4 + chunk_5_4 + chunk_6_4 + chunk_7_4));

	return (block_1 - 1) * (block_1 - 1);
}

bool Jack::contains(vec3 pt, float tolerance)
{
	return getDistanceSq(pt) < ((2 + tolerance) * (2 + tolerance));
}

Point Jack::getPoint(vec3 pt)
{
	return Point();
}

