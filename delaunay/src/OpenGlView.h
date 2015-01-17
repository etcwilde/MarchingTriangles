#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <glfw-cxx/glfw-cxx.hpp>
#include <iostream>
#include <math.h>
#include <string>

#include "world.h"



class OpenGLView : public glfw::Window
{
	public:
		OpenGLView(int width, int height, const std::string &title);
		~OpenGLView();
		void GLPaint();
		void Resize(int width, int height);

		World& get_world();
	private:
		float m_aspect_ratio;
		World m_world;
};
#endif // OPENGLVIEW_H
