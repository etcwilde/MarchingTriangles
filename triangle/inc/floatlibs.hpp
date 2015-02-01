#ifndef FLOATLIB_H
#define FLOATLIB_H

#include <cfloat>

inline bool f_is_zero(float a)
{ return ((a == 0 + FLT_EPSILON) || (a == 0 - FLT_EPSILON)); }

inline int f_sign(float x)
{
	return (f_is_zero(x) ? 0 : ( x < 0 ? -1 : 1 ));
}

inline float f_equ(float a, float b)
{
	return((a == b + FLT_EPSILON) || (a == b - FLT_EPSILON));
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
