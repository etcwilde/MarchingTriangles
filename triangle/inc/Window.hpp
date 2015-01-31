#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <string>

class GWindow
{
	public:
		virtual void GError(int error, const char* description){}
		virtual void GResize(int width, int height){}
		virtual void G

	private:
		// Window object
		GLFWwindow* m_window;

		std::string windowTitle;
};


#endif //WINDOW_H
