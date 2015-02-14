#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "World.hpp"


/**
 * \class Window
 * \brief Basic glfw window c++ wrapper
 */

class Window
{
public:
	/**
	 * \brief Default Window constructor
	 * Generates a 1024x640 window without a title, a designated monitor,
	 * and no shared contexts
	 */
	Window();

	/**
	 * \brief Normal Window constructor
	 * Generates a width x height window with a defined title, monitor, and
	 * shared context.
	 * @param width initial width of the window
	 * @param height initial height of the window
	 * @param title of the window
	 * @param monitor monitor of the widow, default is NULL
	 * @param share Shared window context, default is NULL
	 */
	Window(int width, int height, std::string title,
			GLFWmonitor* monitor=NULL, GLFWwindow* share=NULL);
	~Window();

	void mainloop();

	void destroyWindow();

protected:
	/**
	 * \brief Error handler
	 *
	 * @param error GLFW error code
	 * @param description error message
	 */
	static void errorEvent(int error, const char* description);

	/**
	 * \brief handles window resizes
	 *
	 * @param w window being resized
	 * @param width new window width
	 * @param height new window height
	 */
	static void resizeEvent(GLFWwindow* w, int width, int height);

	/**
	 * \brief handles mouse button presses
	 *
	 * @param w window being clicked
	 * @param button The button being pressed, is one of:
	 * GLFW_MOUSE_BUTTON_1 ... GLFW_MOUSE_BUTTON_8, or
	 * GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_MIDDLE,
	 * GLFW_MOUSE_BUTTON_RIGHT
	 *
	 * @param action Whether the button is being pressed or released, is
	 * one of: GLFW_PRESS or GLFW_RELEASE
	 * @param mods Modifying keys being held, is one of: GLFW_MOD_ALT,
	 * GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_SUPER
	 */
	static void mouseButtonEvent(GLFWwindow* w, int button, int action,
			int mods);

	/**
	 * \brief handles mouse movements
	 *
	 * @param w window where event is occurring
	 * @param x the x coordinate on the window where the click is occurring
	 * @param y the y coordinate on the window where the click is occurring
	 */
	static void mouseMoveEvent(GLFWwindow* w, double x, double y);

	/**
	 * \brief handles scroll events
	 *
	 * @param w window being scrolled
	 * @param x amount scrolled in the x direction
	 * @param y amount scrolled in the y direction
	 */
	static void scrollEvent(GLFWwindow* w, double x, double y);

	/**
	 * \brief handles keys being pressed
	 *
	 * @param w selected window when key press event occurred
	 * @param key GLFW key enum
	 * @param scancode The key-specific code for when GLFW does not handle
	 * the key
	 * @param action The action the key is making, is one of GLFW_PRESS,
	 * GLFW_RELEASE, GLFW_REPEAT
	 */
	static void keyboardEvent(GLFWwindow* w, int key, int scancode,
			int action, int mods);

	/**
	 * \brief handles redrawing the window
	 *
	 * @param w the window being redrawn
	 */
	static void redrawEvent(GLFWwindow* w);


private:
	void init(int width, int height, const char* d, GLFWmonitor* monitor,
			GLFWwindow* share);


	GLFWwindow * m_window;
	World * m_world;

};

#endif
