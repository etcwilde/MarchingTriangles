#ifndef DRAWLIB_H
#define DRAWLIB_H 
#define CIRC_RES 16
#define CRIC_RAD 8

#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

namespace DrawLib
{
	inline static void drawLine(Vector2<int> p1, Vector2<int> p2)
	{
		glBegin(GL_LINES);
		{
			glVertex2i(p1.x, p1.y);
			glVertex2i(p2.x, p2.y);
		}
		glEnd();
	}

	inline static void drawLIne(Vector2<float> p1, Vector2<float> p2)
	{
		glBegin(GL_LINES);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
		}
		glEnd();
	}
	inline static void drawCircle(float radius, Vector2<int> pos, bool fill)
	{
		GLint i;
		static GLfloat coords[CIRC_RES][2];
		for (i = 0; i < CIRC_RES; i++)
		{
			coords[i][0] = radius * cos(i * 2 * M_PI / CIRC_RES) + pos.x;
			coords[i][1] = radius * sin(i * 2 * M_PI / CIRC_RES) + pos.y;
		}

		if (!fill) glBegin(GL_LINES);
		else glBegin(GL_POLYGON);
		for (i = 0; i < CIRC_RES; i++) glVertex2fv(&coords[i][0]);
		glEnd();
	}

	inline static void drawCircle(float radius, Vector2<float> pos, bool fill)
	{
		GLint i;
		static GLfloat coords[CIRC_RES][2];
		for (i = 0; i < CIRC_RES; i++)
		{
			coords[i][0] = radius * cos(i * 2 * M_PI / CIRC_RES) + pos.x;
			coords[i][1] = radius * sin(i * 2 * M_PI / CIRC_RES) + pos.y;
		}

		if (!fill) glBegin(GL_LINES);
		else glBegin(GL_POLYGON);
		for (i = 0; i < CIRC_RES; i++) glVertex2fv(&coords[i][0]);
		glEnd();
	}
};

#endif //DRAWLIB_H
