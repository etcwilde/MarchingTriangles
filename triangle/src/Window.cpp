#include "Window.hpp"
#include <iostream>

BaseWindow::BaseWindow()
{
	init(640, 480, "GL Window", NULL, NULL);
}

BaseWindow::BaseWindow(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share)
{
	init(width, height, title, monitor, share);
}

BaseWindow::~BaseWindow()
{
	destroy();
}

void BaseWindow::init(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share)
{
	//glfwSetErrorCallback(BaseWindow::ErrorCallback);
	if(!glfwInit()) exit(EXIT_FAILURE);
	m_window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	// Set input callbacks
	/*glfwSetKeyCallback(m_window, KeyCallback); // Keyboard
	glfwSetMouseButtonCallback(m_window, MouseCallback);

	// Set output callbacks
	glfwSetWindowSizeCallback(m_window, ResizeCallback); // Resize
	glfwSetWindowRefreshCallback(m_window, RefreshCallback); */
}

void BaseWindow::destroy()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void BaseWindow::ErrorCallback(int code, const char* description)
{
#ifdef DEBUG
	std::cerr << "[Error: " << code << "] " << description << '\n';
#endif // DEBUG
	//ErrorEvent(code, std::string(description));
}

void BaseWindow::ResizeCallback(GLFWwindow* w, int width, int height)
{
	/*if (m_window != w) return;
#ifdef DEBUG
	std::cout << "Resize: " << width << 'x' << height << '\n';
#endif // DEBUG
	ResizeEvent(width, height); */
}

void BaseWindow::RefreshCallback(GLFWwindow* w)
{
	/*if(m_window != w) return;
#ifdef DEBUG
	std::cout << "Redraw\n";
#endif // DEBUG */
}

void BaseWindow::MouseCallback(GLFWwindow* w, int button, int action, int mod)
{
	//if (m_window != w) return;
	/*
#ifdef DEBUG
	std::cout << "Mouse active\n";
#endif
	if (action == GLFW_PRESS) MousePressEvent(button, mod);
	else if (action == GLFW_RELEASE) w->MouseReleaseEvent(button, mod);
#ifdef DEBUG
	else std::cerr << "Unknown Mouse State: " << action << '\n';
#endif */
}

void BaseWindow::ScrollCallback(GLFWwindow* w, double xoff, double yoff)
{
	//if (m_window != w) return;
	/*
#ifdef DEBUG
	std::cout << "Mouse Scroll: " << xoff << 'x' << yoff << '\n';
#endif
	*/

}
