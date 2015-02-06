#ifndef WINDOW_H
#define WINDOW_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <string>

/**
 * \class BaseWindow
 * \brief Wrapper for GLFW handling some functionality
 *
 */

class BaseWindow
{
	public:
		/**
		 * \brief Default window constructor
		 *
		 * Creates a window that is 640x480 with a default title
		 */
		BaseWindow();

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
		BaseWindow(int width, int height, std::string title, GLFWmonitor* monitor=NULL, GLFWwindow* share=NULL);

		~BaseWindow();
	protected:

		/**
		 * \brief Error handler
		 *
		 * Any error messages that GLFW generates are passed to
		 * ErrorEvent
		 *
		 * @param error_code The error code
		 * @param description The error message
		 */
		static void ErrorEvent(int error_code, std::string description);

		/**
		 * \brief Resize Handler
		 *
		 * Called when the viewport dimensions change
		 * @param width The new width of the viewport
		 * @param height The new height of the viewport
		 */
		virtual void ResizeEvent(int width, int height){}

		/**
		 * \brief Redraw the screen
		 *
		 * Called when the screen needs to be redrawn
		 */
		virtual void RedrawEvent(){}

		/**
		 * \brief Catches mouse press events
		 *
		 * @param button The mouse button pressed, this is a GLFW enum
		 * @param mods The keyboard modifier buttons that are pressed
		 * Can be GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
		 * GLFW_MOD_SUPER.
		 */
		virtual void MousePressEvent(int button, int mods){}

		/**
		 * \brief Catches mouse release events
		 *
		 * @param button The mouse button being released.
		 * @param mods The keyboard modifier buttons that are pressed
		 * Can be GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
		 * GLFW_MOD_SUPER.
		 */
		virtual void MouseReleaseEvent(int button, int mods){}

		/**
		 * \brief Catches mouse scroll events
		 *
		 * @param x Scroll offset along the x
		 * @param y Scroll offset along the y -- Normal mouse
		 */
		virtual void MouseScrollEvent(double x, double y){}



		/**
		 * \brief Catches a key press
		 *
		 * @param key The id of the key
		 * @param scancode Code for keys not bound to GLFW
		 * @param mods Modifier keys currently pressed. One of
		 * GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
		 * GLFW_MOD_SUPER
		 */
		virtual void KeyPressEvent(int key, int scancode, int mods){}

		/**
		 * \brief Catches a key release
		 *
		 * @param key The id of the key
		 * @param scancode Code for keys not bound to GLFW
		 * @param mods Modifier keys currently pressed. One of
		 * GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
		 * GLFW_MOD_SUPER
		 */
		virtual void KeyReleaseEvent(int key, int scancode, int mods){}

		/**
		 * \brief Catches when the window gains focus
		 */
		virtual void FocusEvent(){}

		/**
		 * \brief Catches when the window loses focus
		 */
		virtual void UnFocusEvent(){}


	private:
		// The actual callbacks
		static void ErrorCallback(int code, const char * description);
		static void ResizeCallback(GLFWwindow* w, int width, int height);
		static void RefreshCallback(GLFWwindow* w);
		static void MouseCallback(GLFWwindow* w, int button, int action, int mod);
		static void ScrollCallback(GLFWwindow* w, double xoff, double yoff);
		static void KeyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
		static void FocusCallback(GLFWwindow* w, int foc);

		void init(int width, int height, std::string title,
				GLFWmonitor* monitor, GLFWwindow* share);

		void destroy();


		// Window object
		GLFWwindow* m_window;
};


#endif //WINDOW_H
