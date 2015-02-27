/**
 * Window
 *
 * File: 	Window.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Jan 30 2015
 */

#include "Window.hpp"

#include <GLFW/glfw3.h>

Window::Window()
{
	init(1024, 640, "", NULL, NULL);
}

Window::Window(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share)
{
	init(width, height, title.c_str(), monitor, share);
}

Window::~Window()
{
}

void Window::init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	glfwSetErrorCallback(errorEvent);
	if (!glfwInit()) exit(EXIT_FAILURE);

	m_window = glfwCreateWindow(width, height, title, monitor, share);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	// Set callbacks
	glfwSetWindowSizeCallback(m_window, resizeEvent);
	glfwSetMouseButtonCallback(m_window, mouseButtonEvent);
	glfwSetCursorPosCallback(m_window, mouseMoveEvent);
	glfwSetScrollCallback(m_window, scrollEvent);
	glfwSetKeyCallback(m_window, keyboardEvent);
	glfwSetWindowRefreshCallback(m_window, redrawEvent);

	// Set hints
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Opengl versin 330
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	redrawEvent(m_window);
	m_world = &World::getWorldInstance();
}

void Window::mainloop()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	resizeEvent(m_window, width, height);
	glfwSetTime(0.0f);
	double last_time = glfwGetTime();
	double current_time = 0;
	int frames = 0;
	while (!glfwWindowShouldClose(m_window))
	{
		current_time = glfwGetTime();
		m_world->Draw();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		frames++;
		if (current_time - last_time >= 1.0)
		{
			std::cout << "fps: " << frames  << '\r' << std::flush;
			frames = 0;
			last_time = current_time;
		}
	}
}


void Window::destroyWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::errorEvent(int error, const char* description)
{
	// print error -- we can get more complex later
	std::cerr << "Error[" << error << "] " << description << '\n';
}

void Window::resizeEvent(GLFWwindow *w, int width, int height)
{
	World::getWorldInstance().resizeEvent(w, width, height);
}

void Window::mouseButtonEvent(GLFWwindow* w, int button, int action, int mods)
{
	if (action == GLFW_PRESS) World::getWorldInstance().mousePressEvent(w,
			button, mods);
	else if (action == GLFW_RELEASE)
		World::getWorldInstance().mouseReleaseEvent(w, button, mods);
	World::getWorldInstance().mouseClickEvent(w, button, action, mods);
}

void Window::mouseMoveEvent(GLFWwindow* w, double x, double y)
{
	World::getWorldInstance().mouseMoveEvent(w, x, y);
}

void Window::scrollEvent(GLFWwindow* w, double x, double y)
{
	World::getWorldInstance().scrollEvent(w, x, y);
}

void Window::keyboardEvent(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(w, GL_TRUE);
		return;
	}

	switch (action)
	{
		case GLFW_PRESS:
			World::getWorldInstance().keyPressEvent(w, key,
					scancode, mods);
			break;
		case GLFW_RELEASE:
			World::getWorldInstance().keyReleaseEvent(w, key,
					scancode, mods);
			break;
		case GLFW_REPEAT:
			World::getWorldInstance().keyHoldEvent(w, key,
					scancode, mods);
	}
}

void Window::redrawEvent(GLFWwindow* w)
{
	// World
	World::getWorldInstance().Draw();
}
