#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <cmath>
#include <cfloat>

/**
 * \class Camera
 * \brief Controls viewing of the world
 * Provides three motion types
 * arc, track, and dolly
 *
 * The arcball used in the camera arc motion utilizes quaternions, which
 * means the camera is not bound to a given axis, and therefore is not
 * susceptible to gimbal lock.
 */

class Camera
{
public:
	Camera();
	Camera(float w, float h);
	~Camera();

	enum class CameraMovement
	{
		IDLE=0, // Not moving
		ARC,  // orbit on the arcball
		TRACK, // Move along the plane
		DOLLY // Move camera in or out -- not zoom
	};

	void setBounds(float w, float h);

	CameraMovement getCameraMovement();

	void mouseDown(const glm::vec2 point, CameraMovement movement);
	glm::mat4 drag(const glm::vec2 point);

protected:
	glm::vec3 mapToSphere(const glm::vec2 point);

private:
	glm::vec3 m_startVector; // Starting point for transformations
	glm::vec3 m_releaseVector; // Distance dragged for transformations
	CameraMovement m_movement; // Type of motion
	float m_width; // Width of screen
	float m_height; // Height of screen
};

#endif
