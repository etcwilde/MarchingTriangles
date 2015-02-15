#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

// Paint colors
//
// TODO: Cyan Magenta Yellow colors

/**
 * \class Color
 * \brief Behaves like colors found on materials or paints
 *
 * When added to or subtracted from other colors, it behaves like mixing paints
 * rather than mixing light values.
 */
class Color
{
public:
protected:
private:
};

class ColorRGB : Color
{
public:
	ColorRGB();
	ColorRGB(float r, float g, float b);

	inline float r() const;
	inline float g() const;
	inline float b() const;

	const float* data() const;

	void operator += (const ColorRGB& color);
	void operator -= (const ColorRGB& color);

	ColorRGB operator + (const ColorRGB& color) const;
	ColorRGB operator - (const ColorRGB& color) const;

	// ColorRGBA operator + (const ColorRGBA& color) const;
	// ColorRGBA operator - (const ColorRGBA& color) const;

private:
	union
	{
		struct {float R; float G; float B;};
		float m_vals[3];
	};
};

class ColorRGBA : Color
{
private:
	union
	{
		struct {float R; float G; float B; float A;};
		float m_vals[4];
	};
};

class ColorHSL : Color
{
private:
	union
	{
		struct {float H; float S; float L;};
		float m_vals[3];
	};
};

class ColorHSLA : Color
{
private:
	union
	{
		struct {float H; float S; float L; float A;};
		float m_vals[4];
	};
};

// Light colors
//
/**
 * \class Radiance
 * \brief Behaves like light
 *
 * This is for storing the colors of lights. Behaviours are similar to light,
 * intensity calculations can be done, and they mix when added.
 */
class Radiance
{
public:
	virtual float intensity()=0;
	virtual float intensity() const =0;
protected:
private:
};

class RadianceRGB : Radiance
{
private:
	union
	{
		struct {float R; float G; float B;};
		float m_vals[3];
	};
};

class RadianceHSL: Radiance
{
private:
	union
	{
		struct {float H; float S; float L;};
		float m_vals[3];
	};
};


#endif // COLOR_H
