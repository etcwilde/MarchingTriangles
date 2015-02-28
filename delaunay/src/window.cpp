#include "window.h"

Window::Window(std::string fname)
{
	init(1024, 640, "", fname, NULL, NULL);
}

Window::Window(int width, int height, std::string title, std::string fname,
			GLFWmonitor* m, GLFWwindow* share)
{
	init(width, height, title.c_str(), fname, m, share);
}

Window::~Window()
{ }

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
		if (current_time - last_time >= 1.f)
		{
			std::cout << "fps: " << frames << '\r' << std::flush;
			frames = 0;
			last_time = current_time;
		}
	}
}

void Window::destroywindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::errorEvent(int error, const char* desc)
{
	std::cerr << "Error: " << std::hex << error << ": " << desc << '\n';
}

void Window::resizeEvent(GLFWwindow* w, int width, int height)
{
	World::getWorldInstance().resizeEvent(w, width, height);
}

void Window::keyboardEvent(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(w, GL_TRUE);
		return;
	}


	if (action == GLFW_PRESS)
	{
		World::getWorldInstance().keyPressEvent(w, key, scancode, mods);
	}
}

void Window::redrawEvent(GLFWwindow *w)
{
	World::getWorldInstance().Draw();
}

void Window::init(int width, int height, const char* title, std::string fname,
		GLFWmonitor* m, GLFWwindow *w)
{
	glfwSetErrorCallback(errorEvent);
	if (!glfwInit()) exit(EXIT_FAILURE);
	m_window = glfwCreateWindow(width, height, title, m,w);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);

	glfwSetWindowSizeCallback(m_window, resizeEvent);
	glfwSetKeyCallback(m_window, keyboardEvent);
	glfwSetWindowRefreshCallback(m_window, redrawEvent);

	redrawEvent(m_window);
	m_world = &World::getWorldInstance();
	FileLoader data_loader;
	data_loader.LoadPolygons(m_world, fname);
}

