#include "Perlin.hpp"

float NoiseGenerator::generateNoise(float x, float y, float z)
{
	return generateNoiseScaled(x * m_scale_x, y * m_scale_y, z * m_scale_z);
}

PerlinNoise::PerlinNoise() :
	NoiseGenerator(),
	m_persistence(0.5f),
	m_octaves(4)
{}

PerlinNoise::PerlinNoise(float scale_x, float scale_y, float scale_z) :
	NoiseGenerator(scale_x, scale_y, scale_z),
	m_persistence(0.5f),
	m_octaves(4)
{}

PerlinNoise::PerlinNoise(float persistence) :
	NoiseGenerator(),
	m_persistence(persistence),
	m_octaves(4)
{}

PerlinNoise::PerlinNoise(float persistence, int octaves) :
	NoiseGenerator(),
	m_persistence(persistence),
	m_octaves(octaves)
{}

PerlinNoise::PerlinNoise(float persistence, int octaves, float scale) :
	NoiseGenerator(scale),
	m_persistence(persistence),
	m_octaves(octaves)
{}

PerlinNoise::PerlinNoise(float persistence, int octaves, float scale_x,
		float scale_y, float scale_z) :
	NoiseGenerator(scale_x, scale_y, scale_z),
	m_persistence(persistence),
	m_octaves(octaves)
{}

float PerlinNoise::noise(int x, int y, int z)
{
	int n = x + y * 57 + z * 131;
	n = (n << 13) ^ n;
	return(1.f-((n*(n*n*15731+789221)+1376312589)&0x7fffffff)/1073741824.f);
}

float PerlinNoise::smoothNoise(int x, int y, int z)
{
	float corners = (
			noise(x-1, y-1, z-1)+
			noise(x+1, y-1, z-1)+
			noise(x-1, y+1, z-1)+
			noise(x+1, y+1, z-1)+
			noise(x-1, y-1, z+1)+
			noise(x+1, y-1, z+1)+
			noise(x-1, y+1, z+1)+
			noise(x+1, y+1, z+1)) / 32.f;

	float sides = (
			noise(x+1, y+1, z)+
			noise(x-1, y+1, z)+
			noise(x+1, y-1, z)+
			noise(x-1, y-1, z)+
			noise(x+1, y, z+1)+
			noise(x-1, y, z+1)+
			noise(x+1, y, z-1)+
			noise(x-1, y, z-1)+
			noise(x, y+1, z+1)+
			noise(x, y-1, z+1)+
			noise(x, y+1, z-1)+
			noise(x, y-1, z-1)) / 24.f;
	float center = noise(x, y, z) / 4.f;

	return corners + sides + center;
}

float PerlinNoise::linearInterpolation(float a, float b, float x)
{
	return a * (1-x) + b * x;
}

float PerlinNoise::cosineInterpolation(float a, float b, float x)
{
	float ft = x * M_PI;
	float f = (1 - std::cos(ft)) * 0.5f;
	return a*(1-f) + b * f;
}

float PerlinNoise::interpolatedNoise(float x, float y, float z)
{
	int _x = fastFloor(x);
	int _y = fastFloor(y);
	int _z = fastFloor(z);
	float fract_x = x - _x;
	float fract_y = y - _y;
	float fract_z = z - _z;

	float vert1 = smoothNoise(_x, 	_y, 	_z);
	float vert2 = smoothNoise(_x+1, _y,	_z);
	float vert3 = smoothNoise(_x, 	_y+1,	_z);
	float vert4 = smoothNoise(_x+1, _y+1, 	_z);
	float vert5 = smoothNoise(_x, 	_y, 	_z+1);
	float vert6 = smoothNoise(_x+1,	_y, 	_z+1);
	float vert7 = smoothNoise(_x, 	_y+1, 	_z+1);
	float vert8 = smoothNoise(_x+1,	_y+1, 	_z+1);

	float i1 = cosineInterpolation(vert1, vert2, fract_x);
	float i2 = cosineInterpolation(vert3, vert4, fract_x);
	float i3 = cosineInterpolation(vert5, vert6, fract_x);
	float i4 = cosineInterpolation(vert7, vert8, fract_x);

	float i5 = cosineInterpolation(i1, i2, fract_y);
	float i6 = cosineInterpolation(i3, i4, fract_y);

	return cosineInterpolation(i5, i6, fract_z);
}

float PerlinNoise::generateNoiseScaled(float x, float y, float z)
{
	float total = 0;
	//float max = 0;
	float frequency = 1.f/2;
	float amplitude = 1 / m_persistence;
	for (int i = 0; i < m_octaves; i++)
	{
		frequency *= 2;
		amplitude *= m_persistence;
		total += interpolatedNoise(
				x * frequency * m_scale_x,
				y * frequency * m_scale_y,
				z * frequency * m_scale_z) * amplitude;
	//	max += amplitude;
	}
	return total;
}
