/*
 * Perlin
 *
 * File: 	Perlin.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 26 2015
 */

#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <cmath>

class NoiseGenerator
{
public:
	NoiseGenerator() :
		m_scale_x(1.f),
		m_scale_y(1.f),
		m_scale_z(1.f)
	{}

	NoiseGenerator(float scale) :
		m_scale_x(scale),
		m_scale_y(scale),
		m_scale_z(scale)
	{}

	NoiseGenerator(float scale_x, float scale_y, float scale_z) :
		m_scale_x(scale_x),
		m_scale_y(scale_y),
		m_scale_z(scale_z)
	{}
	virtual ~NoiseGenerator(){}
	float generateNoise(float x, float y, float z);

protected:

	virtual float generateNoiseScaled(float x, float y, float z)=0;

	float m_scale_x;
	float m_scale_y;
	float m_scale_z;
private:
};

class PerlinNoise : public NoiseGenerator
{
public:
	PerlinNoise();
	PerlinNoise(float scale_x, float scale_y, float scale_z);
	PerlinNoise(float persistence);
	PerlinNoise(float persistence, int octaves);
	PerlinNoise(float persistence, int octaves, float scale);
	PerlinNoise(float persistence, int octaves, float scale_x,
			float scale_y, float scale_z);

	virtual ~PerlinNoise() {}

protected:
	virtual float generateNoiseScaled(float x, float y, float z);
	inline int fastFloor(const float x) {return x > 0 ? (int)x : (int)x-1;}
	float noise(int x, int y, int z);
	float smoothNoise(int x, int y, int z);
	float linearInterpolation(float a, float b, float x);
	float cosineInterpolation(float a, float b, float x);
	float interpolatedNoise(float x, float y, float z);

	float m_persistence;
	int m_octaves;
};

class MarbleNoise : public PerlinNoise
{
public:
	MarbleNoise() :
		PerlinNoise()
	{}

	MarbleNoise(float persistence) :
		PerlinNoise(persistence)
	{}

	MarbleNoise(float persistence, int octaves) :
		PerlinNoise(persistence, octaves)
	{}

protected:
	float generateNoiseScaled(float x, float y, float z)
	{
		return std::cos(x+90*PerlinNoise::generateNoiseScaled(x, y, z));
	}
};

class GrainNoise : public PerlinNoise
{
public:
	GrainNoise() :
		PerlinNoise()
	{}

	GrainNoise(float persistence) :
		PerlinNoise(persistence)
	{}

	GrainNoise(float persistence, int octaves) :
		PerlinNoise(persistence, octaves)
	{}
protected:
	float generateNoiseScaled(float x, float y, float z)
	{
		float grain = PerlinNoise::generateNoiseScaled(x,y,z)*20;
		return grain - fastFloor(grain);
	}
};



#endif
