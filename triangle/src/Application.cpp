#include "Application.hpp"

Application::Application(int argc, char** argv)
{
	if (!glfwInit()) exit(EXIT_FAILURE);
}

Application::~Application()
{
	// Not sure yet
}

void Application::CreateWindow()
{
}

void Application::CreateWindow(int width, int height, std::string title)
{

}


// Private methods

BaseWindow* Application::find_base(GLFWwindow* w)
{
	for(unsigned int i =0; i < m_windows.size(); ++i)
	{
		if (m_windows[i].w == w) return m_windows[i].bw;
	}
	return NULL;
}
