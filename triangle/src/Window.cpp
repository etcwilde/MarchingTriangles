#include "Window.hpp"
#include <iostream>

Window::Window()
{
	init(640, 480, "GL Window", NULL, NULL);
}

Window::Window(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share)
{
	init(width, height, title, monitor, share);
}

Window::~Window()
{
}

void Window::init(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share)
{
	glfwSetErrorCallback(Window::ErrorCallback);
	if(!glfwInit()) exit(EXIT_FAILURE);
	m_window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	// Set input callbacks

	// Set output callbacks

}

void Window::ErrorCallback(int code, const char* description)
{
	//std::cerr << "[Error: " << code << "] " << description << '\n';
	ErrorEvent(code, std::string(description));
}

void Window::ResizeCallback(GLFWwindow* w, int width, int height)
{
	if (m_window != w) break;
	ResizeEvent(width, height);
}

void Window::RefreshCallback(GLFWwindow* w)
{
	if(m_window != w) break;
	// Otherwise this is our window
	// Call our callback function
	RedrawEvent();
}

