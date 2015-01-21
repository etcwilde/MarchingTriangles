#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <glfw-cxx/glfw-cxx.hpp>

#include <math.h>

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

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

		void initialize();
		void terminate();

		std::string m_title;
		int m_initial_width, m_initial_height;
		int m_width, m_height;

		void run();
		float m_aspect_ratio;

		World* m_world;

		/* Threading stuff */

		void t_redraw();
		void t_event();
		void t_main();

		bool m_b_kill; // Program is shutting down.

		// Lock the redraw
		std::mutex m_redraw;
		std::mutex m_mb_redraw; // Protects the redraw boolean
		std::condition_variable m_cv_redraw;
		bool m_b_redraw; 	// Do we need to redraw?

		std::thread thread_redraw;
		std::thread thread_event;
		std::thread thread_main;

};
#endif // OPENGLVIEW_H
