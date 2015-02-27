/**
 * Camera
 *
 * File: 	Camera.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 6 2015
 */

#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#define M_PI180 0.017453292519943295

#define C_MAX_FOV 46.6f
#define C_MIN_FOV 44.f

/**
 * \class Camera
 * \brief A basic camera
 *
 * Three movement types for the camera, dolly, strafe, and rotate
 */
using namespace glm;

class Camera
{
public:
	/**
	 * \brief Default Camera constructor
	 *
	 * Creates the camera at position 1, 0, 0 looking at 0, 0, 0
	 */
	Camera();

	/**
	 * \brief Applies the current camera position to the viewer
	 */
	void Render();

	/**
	 * \brief Move Camera
	 * \param direction The direction and magnitude to move camera
	 *
	 * Moves the camera relative to the current position in the given
	 * direction. The distance is defined by the magnitude of the direction
	 * vector.
	 */
	void move_camera(vec3 direction);

	/**
	 * \brief Place Camera
	 * \param position x, y, z coordinate to set camera
	 *
	 * Places the camera at the position defined by position. The direction
	 * the camera is looking should remain the same.
	 */
	void place_camera(vec3 position);

	/**
	 * \brief Change where the camera is looking
	 * \param position The coordinates where the camera is looking
	 *
	 * Changes the camera lookat position to the new position.
	 */
	void set_view(vec3 position);

	/**
	 * \brief rotate X
	 * \param angle How much to rotate the camera
	 *
	 * Rotates the camera around the x axis by a given angle
	 */
	void rotate_x(GLfloat angle);

	/**
	 * \brief rotate Y
	 * \param angle How much to rotate the camera
	 *
	 * Rotates the camera around the Y axis by a given angle
	 */
	void rotate_y(GLfloat angle);

	/**
	 * \brief rotate Z
	 * \param angle How much to rotate the camera
	 *
	 * Rotates the camera around the z axis by a given angle
	 */
	void rotate_z(GLfloat angle);

	/**
	 * \brief Dollies camera
	 * \param distance Amount to dolly camera
	 *
	 * Moves camera along the view vector a given distance. Negative
	 * distance will result in the camera getting further from the lookat
	 * position.
	 */
	void move_forward(GLfloat distance);

	/**
	 * \brief Allows the camera to pan right and left
	 * \param distance Amount to move right
	 *
	 * Moves the camera along the right vector a given distance. Positive
	 * distance will result in the camera moving right, negative distance
	 * will result in the camera moving left.
	 */
	void strafe_right(GLfloat distance);

	/**
	 * \brief Moves the camera up
	 * \param distance Amount to move up
	 *
	 * Move the camera along the up-vector Positive distance will result in
	 * the camera moving up, negative distance will result in the camera
	 * moving down.
	 */
	void strafe_up(GLfloat distance);


	void rotate_horizontal(GLfloat distance);

	void rotate_vertical(GLfloat distance);


	/**
	 * \brief set the camera field of view
	 */
	void set_fov(GLfloat fov);

	/**
	 * \brief adjust the field of view on the camera
	 */
	void adjust_fov(GLfloat delta);

	void set_bounds(GLint width, GLint height);


	/**
	 * \brief Current position
	 *
	 * Returns the current position of the camera
	 */
	inline vec3 Position() const { return m_position; }

	/**
	 * \brief View to vector
	 *
	 * Returns the direction the camera is currently looking
	 */
	inline vec3 View() const { return m_direction; }

	/**
	 * \brief Returns if the camera is orthographic
	 *
	 */
	inline bool is_ortho() const { return m_ortho; }


	/**
	 * \brief Returns the camera field of view
	 */
	inline GLfloat Fov() const { return m_fov; }

private:
	vec3 m_position; // Current position
	vec3 m_direction; // Lookat position
	vec3 m_updir; // Up vector

	float m_rotate_distance; // Distance at which we rotate

	mat4 m_VP; // View Perspective Matrix
	mat4 m_View; // View matrix
	mat4 m_Persp; // Perspective Matrix;

	// Are the cached matrices good
	bool m_VP_good;
	bool m_View_good;
	bool m_Persp_good;

	GLfloat m_fov;
	GLfloat m_rotateX, m_rotateY, m_rotateZ;

	GLint m_width, m_height;

	bool m_ortho;
};

#endif
