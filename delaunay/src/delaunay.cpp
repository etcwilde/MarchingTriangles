#include "delaunay.h"

static bool CircleIntersect(Vector2<float> test_point,
		Vector2<float> p1, Vector2<float> p2, Vector2<float> p3,
		Vector2<float>& centre_point, float& r)
{
	float m1, m2, mx1, mx2, my1, my2;
	float dx, dy, rsqr, drsqr;

	if (abs(p1.y - p2.y) < DEL_EPS && abs(p2.y - p3.y) < DEL_EPS)
		return false;

	if (abs(p2.y - p1.y) < DEL_EPS)
	{
		m2 = - (p3.x - p2.x) / (p3.y - p2.y);
		mx2 = (p2.x + p3.x) / 2.0;
		my2 = (p2.y + p3.y) / 2.0;
		// Centre point
		centre_point.x = (p2.x + p1.x) / 2.0;
		centre_point.y = m2 * (centre_point.x - mx2) + my2;
	}
	else if(abs(p3.y - p2.y) < DEL_EPS)
	{
		m1 = -(p2.x - p1.x) / (p2.y - p1.y);
		mx1 = (p1.x + p2.x) / 2.0;
		my1 = (p1.y + p2.y) / 2.0;
		centre_point.x = (p3.x + p2.x) / 2.0;
		centre_point.y + m1 * (centre_point.x - mx1) + my1;
	}
	else
	{
		m1 = -(p2.x - p1.x) / (p2.y - p1.y);
		m2 = -(p3.x - p2.x) / (p3.y - p2.y);
		mx1 = (p1.x + p2.x) / 2.0;
		mx2 = (p2.x + p3.x) / 2.0;
		my1 = (p1.y + p2.y) / 2.0;
		my2 = (p2.y + p3.y) / 2.0;
		centre_point.x = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
		centre_point.y = m1 * (centre_point.x - mx1) + my1;
	}

	dx = p2.x - centre_point.x;
	dy = p2.y - centre_point.y;
	rsqr = dx * dx + dy * dy;
	r = sqrt(rsqr);
	dx = test_point.x - centre_point.x;
	dy = test_point.y - centre_point.y;
	drsqr = dx * dx + dy * dy;
	return (drsqr <= rsqr);
}
