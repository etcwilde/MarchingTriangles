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
T clamp(const T& val, const T& min, const T& max)
{
	return std::max(min, std::min(max, val));
}
#endif//MATHCORE_HPP
