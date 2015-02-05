#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <string>

/**
 * \class GLFWWindow
 * \brief Wrapper for GLFW handling some functionality
 *
 */

class GLFWWindow
{
	public:
		/**
		 * \brief Default window constructor
		 *
		 * Creates a window that is 640x480 with a default title
		 */
		GLFWWindow();

		/**
		 * \brief Advanced window constructor
		 * @param width The initial screen width
		 * @param height The initial screen height
		 * @param title The window title
		 * @param monitor The monitor to be used. If NULL, it creates a
		 * standard window.
		 * @param share The window to share contexts with. NULL if
		 * there are none.
		 */
		GLFWWindow(int width, int height, std::string title, GLFWmonitor* monitor=NULL, GLFWwindow* share=NULL);

	protected:

		virtual void ErrorEvent(int error_code, std::string description)=0;
		virtual void ResizeEvent(int width, int height)=0;
		virtual void RedrawEvent()=0;


	private:

			// The actual callbacks
		void ErrorCallback(int code, const char * description);
		void ResizeCallback(GLFWwindow* w, int width, int height);
		void RefreshCallback(GLFWwindow* w);

	void init(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share);

		// Window object
		GLFWwindow* m_window;

		std::string windowTitle;
};


#endif //WINDOW_H
