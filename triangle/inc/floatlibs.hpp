/**
 * floatlibs
 *
 * File: 	floatlibs.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Jan 31 2015
 */

#ifndef FLOATLIB_H
#define FLOATLIB_H

#include <cfloat>

#include <iostream>



inline float f_equ(float a, float b)
{
	//std::cerr << a << "==" << b << '\n';
	return((a == b + FLT_EPSILON) || (a == b - FLT_EPSILON) || (a == b));
}

inline float f_equ(float a, float b, float eps)
{
	//std::cerr << a << "==" << b << '\n';
	return((a == b + eps) || (a == b - eps) || (a == b));
}

inline bool f_is_zero(float a)
{
	return f_equ(a, 0);
}

inline int f_sign(float x)
{
	return (f_is_zero(x) ? 0 : ( x < 0 ? -1 : 1 ));
}

inline float f_ge(float a, float b)
{
	//std::cerr << a << ">=" << b << '\n';
	return a >= b - FLT_EPSILON;
}

inline float f_le(float a, float b)
{
	//std::cerr << a << "<=" << b << '\n';
	return a <= b + FLT_EPSILON;
}

inline float f_lt(float a, float b)
{
	//std::cerr << a << '<' << b << '\n';
	return (a < b + FLT_EPSILON || a < b - FLT_EPSILON);
}

inline float f_gt(float a, float b)
{
	//std::cerr << a << '>' << b << '\n';
	return (a > b - FLT_EPSILON || a > b + FLT_EPSILON);
}

inline float f_div(float a, float b)
{
	if (f_is_zero(b))
	{
		if (f_is_zero(a)) return 0;
		else return FLT_MAX * f_sign(a);
	}
	else
	{
		if (f_is_zero(a)) return 0;
		else
		{
			if ((a + b) == a)
				return FLT_MAX * f_sign(a) * f_sign(b);
			else return a / b;
		}
	}
}


#endif //FLOATLIB_H
