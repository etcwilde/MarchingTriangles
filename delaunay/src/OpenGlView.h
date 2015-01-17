#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <math.h>
#include <list>
#include "polygon.h"
#include <glfw-cxx/glfw-cxx.hpp>
#include <string>
#include <iostream>

class OpenGLView : public glfw::Window
{
	public:
		OpenGLView(int width, int height, const std::string &title);
		~OpenGLView();
		void GLPaint();
		void Resize(int width, int height);
	private:
		std::list<Polygon> m_polygons;
		glfw::FramebufferSize m_fb_size;
		float m_aspect_ratio;
};

#endif // OPENGLVIEW_H
