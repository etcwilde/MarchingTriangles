#ifndef MATHCORE_HPP
#define MATHCORE_HPP
#include <cmath>

/**
 * \brief Clamps a value between two other values
 *
 * Bounds a value between a max and min value
 * \param val The value being bounded
 * \param min The minimum possible value
 * \param max The maximum possible value
 */


template <typename T>
inline T clamp(const T& val, const T& min, const T& max)
{
	return std::max(min, std::min(max, val));
}

template <typename T>
inline T toDegrees(T radians)
{
	return radians * 57.29577951;
}

template <typename T>
inline T toRadians(T degrees)
{
	return degrees * 0.017453292;
}
#endif//MATHCORE_HPP
