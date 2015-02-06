#include "Window.hpp"

Window::Window()
{
	init(640, 480, "", NULL, NULL);
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

	// Setup opengl
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(5.0f);

	redrawEvent(m_window);
}

void Window::mainloop()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	resizeEvent(m_window, width, height);


	glfwSetTime(0.0f);
	double current_time;
	while (!glfwWindowShouldClose(m_window))
	{
		current_time = glfwGetTime();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
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
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (double)width/height, 1.0, 1024.0);
	//redrawEvent(w);
}

#include <GLFW/glfw3.h>
void Window::mouseButtonEvent(GLFWwindow* w, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "Left Button pressed\n";
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "Right Button pressed\n";
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		std::cout << "Middle Button pressed\n";
}

void Window::mouseMoveEvent(GLFWwindow* w, double x, double y)
{
}

void Window::scrollEvent(GLFWwindow* w, double x, double y)
{
	std::cout << "X scroll: " << x << '\n';
	std::cout << "Y scroll: " << y << '\n';
}

void Window::keyboardEvent(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GL_TRUE);
	if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
		std::cout << "Keypad 0 pressed\n";
	if (key == GLFW_KEY_KP_0 && action == GLFW_REPEAT)
		std::cout << "keypad 0 held down\n";
}

void Window::redrawEvent(GLFWwindow* w)
{
	std::cout << "Redraw\n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


