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

	// Setup opengl
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(5.0f);

	redrawEvent(m_window);

	m_world = &World::getWorldInstance();


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

		m_world->Draw();

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// World
	World::getWorldInstance().Draw();
}


