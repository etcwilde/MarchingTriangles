#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.hpp"

/**
 * \class World
 * \brief Container for all things happening in the universe
 *
 * The world controls camera positioning, objects, and drawing of those
 * objects. It maintains everything.
 */

class World
{
public:
	~World();

	static World& getWorldInstance();

	// Draws the world
	void Draw();


	/**
	 * \brief handles mouse button presses in the world
	 *
	 * @param w window being clicked
	 * @param button The button being pressed, is one of:
	 * GLFW_MOUSE_BUTTON_1 ... GLFW_MOUSE_BUTTON_8, or
	 * GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_MIDDLE,
	 * GLFW_MOUSE_BUTTON_RIGHT
	 *
	 * @param mods Modifying keys being held, is one of: GLFW_MOD_ALT,
	 * GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_SUPER
	 */
	void mousePressEvent(GLFWwindow* w, int button, int mods);

	/**
	 * \brief handles mouse button releases in the world
	 *
	 * @param w window being clicked
	 * @param button The button being pressed, is one of:
	 * GLFW_MOUSE_BUTTON_1 ... GLFW_MOUSE_BUTTON_8, or
	 * GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_MIDDLE,
	 * GLFW_MOUSE_BUTTON_RIGHT
	 *
	 * @param mods Modifying keys being held, is one of: GLFW_MOD_ALT,
	 * GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_SUPER
	 */
	void mouseReleaseEvent(GLFWwindow* w, int button, int mods);
	/**
	 * \brief handles mouse button actions
	 *
	 * @param w window being clicked
	 * @param button The button being pressed, is one of:
	 * GLFW_MOUSE_BUTTON_1 ... GLFW_MOUSE_BUTTON_8, or
	 * GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_MIDDLE,
	 * GLFW_MOUSE_BUTTON_RIGHT
	 *
	 * @param action Whether the button is being pressed or released, is
	 * one of: GLFW_PRESS or GLFW_RELEASE
	 * @param mods Modifying keys being held, is one of: GLFW_MOD_ALT,
	 * GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_SUPER
	 */
	void mouseClickEvent(GLFWwindow*w, int button, int action, int mods);

	void mouseMoveEvent(GLFWwindow* w, double x, double y);

	/**
	 * \brief handles scroll events
	 *
	 * @param w window being scrolled
	 * @param delta_x amount scrolled in the x direction
	 * @param delta_y amount scrolled in the y direction
	 */
	void scrollEvent(GLFWwindow* w, double delta_x, double deta_y);

	/**
	 * \brief handles keys being pressed
	 *
	 * @param w selected window when key press event occurred
	 * @param key GLFW key enum
	 * @param scancode The key-specific code for when GLFW does not handle
	 * the key
	 * @param mods  GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
	 * GLFW_MOD_SUPER
	 */
	void keyPressEvent(GLFWwindow* w, int key, int scancode, int mods);

	/**
	 * \brief handles keys being held
	 *
	 * @param w selected window when key press event occurred
	 * @param key GLFW key enum
	 * @param scancode The key-specific code for when GLFW does not handle
	 * the key
	 * @param mods  GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
	 * GLFW_MOD_SUPER
	 */
	void keyHoldEvent(GLFWwindow* w, int key, int scancode, int mods);

	/**
	 * \brief handles keys being released
	 *
	 * @param w selected window when key press event occurred
	 * @param key GLFW key enum
	 * @param scancode The key-specific code for when GLFW does not handle
	 * the key
	 * @param mods  GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL,
	 * GLFW_MOD_SUPER
	 */
	void keyReleaseEvent(GLFWwindow* w, int key, int scancode, int mods);
	void resizeEvent(GLFWwindow* w, int width, int height);
protected:

private:
	World();

	void draw_coordinates();

	Camera m_camera;

	glm::mat4 m_lastRotation;
	glm::mat4 m_currentRotation;
	glm::mat4 m_lastScale;
	glm::mat4 m_currentScale;
	glm::mat4 m_lastTranslate;
	glm::mat4 m_currentTranslate;

	glm::vec3 m_background_color;
	glm::vec3 m_grid_color;

	bool m_mouseDrag;
	bool m_drawGrid;

	double m_prevTime;
};

#endif //WORLD_H
