#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"

struct window_pair_t
{
	GLFWwindow* w;
	BaseWindow* bw;
};

/**
 * \class Application
 * \brief Manages GUI application control flow
 *
 * Contains the main event loop where all events from the window system and
 * other sources are processed and dispatched. Handles application
 * initialization, finalization.
 *
 * For a given application, there is exactly one Application object.
 */
class Application
{

	Application(int argc, char** argv);
	~Application();

	void CreateWindow();
	void CreateWindow(int width, int height, std::string title);

private:
	//Convert glfw window address to the window object
	std::vector<struct window_pair_t> m_windows;

	/**
	 * \brief Gives the base window address for a given glfw window
	 *
	 * This will be used for handling the callbacks.
	 * @param w The address of the window
	 */
	BaseWindow* find_base(GLFWwindow* w);
};



#endif // APPLICATION_H
