#ifndef FIELDFUNCTIONS_H
#define FIELDFUNCTIONS_H
#include <cmath>

float solidFunction(float dist)
{
	return (dist <= 1.f && dist >= 0.f) ? 1.f : 0.f;
}

float linearFunction(float dist)
{
	return (dist <= 1.f) ? 1.0 - std::sqrt(dist) : 0.f;
}

float parabolicFunction(float dist)
{
	return (dist <= 1.f) ? 1.f - dist : 0.f;
}

float geoffFunction(float dist)
{
	if (dist <= 1.f)
	{
		register float d = dist;
		register float s = d*d;
		register float c = s*d;
		return 1.f-(0.444444444f)*c+(1.888888888f)*s-(2.444444444f)*d;
	}
	else return 0.f;
}

float blinnFunction(float dist)
{
	return std::pow(M_E, -3*dist);
}

float metaballFunction(float dist)
{
	register float d = std::sqrt(dist);
	if (d <= 0.333f) return 1 - 3*dist;
	else if (d < 1.f) return 1.5f * (1-d)*(1-d);
	else return 0.f;
}

float wyvillFunction(float dist)
{
	if (dist < 1.f) return (1 - dist) * ( 1 - dist) * (1 - dist);
	else return 0.f;
}

#endif // FIELDFUNCTIONS_H
