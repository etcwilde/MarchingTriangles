#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "world.h"
#include "fileloader.h"


class Window
{
public:
	Window(std::string fname);
	Window(int width, int height, std::string title, std::string fname,
			GLFWmonitor* m=NULL, GLFWwindow* share = NULL);
	~Window();

	void mainloop();
	void destroywindow();

protected:

	// Resize
	// Redraw
	// Keypress

	static void errorEvent(int error, const char* description);

	static void resizeEvent(GLFWwindow* w, int width, int height);

	static void keyboardEvent(GLFWwindow* w, int key, int scancode,
			int action, int mods);

	static void redrawEvent(GLFWwindow* w);

private:
	void init(int width, int height, const char* title, std::string filename,
			GLFWmonitor*m, GLFWwindow* w);

	GLFWwindow* m_window;
	World* m_world;
};

#endif
