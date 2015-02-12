#ifndef VECOPS_H
#define VECOPS_H

#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace glm;

//Place to keep undefined vector operations

// glm scalar multiplication

/*template <typename T, typename S>
inline tvec3<T> operator*(tvec3<T> const & v, S const & s)
{
	T s1 = T(s);
	return tvec3<T>( v.x * s1, v.y * s1, v.z * s1);
} */

template <typename T>
inline tvec3<T> operator*(tvec3<T> const & v, float const & s)
{
	return tvec3<T>( v.x * s, v.y * s, v.z * s);
}


#endif
