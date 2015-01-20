#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <glfw-cxx/glfw-cxx.hpp>

#include <math.h>

#include <iostream>
#include <string>
#include <thread>

#include "world.h"



class OpenGlView : public glfw::Window
{
	public:
		OpenGlView(int width, int height, const std::string &title);
		OpenGlView(int width, int height, const std::string &title,
				World* world);
		OpenGlView(int width, int height, const std::string &title,
				World world);
		~OpenGlView();

		void GLPaint();
		void Resize(int width, int height);

		const World* get_world() const;
		void set_world(const World& w);
	private:


		/* Thread that actually does the redrawing */
		void t_redraw();
		void t_event();
		void t_main();


		std::string m_title;
		int m_initial_width, m_initial_height;
		int m_width, m_height;

		void run();
		float m_aspect_ratio;

		World* m_world;
};
#endif // OPENGLVIEW_H
