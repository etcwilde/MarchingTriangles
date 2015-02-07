#include "Camera.hpp"

using namespace glm;

Camera::Camera()
{
	m_startVector = vec3(0);
	m_releaseVector = vec3(0);
	m_movement = CameraMovement::IDLE;
}

Camera::Camera(float w, float h)
{
	m_startVector = vec3(0);
	m_releaseVector = vec3(0);
	m_movement = CameraMovement::IDLE;
	setBounds(w, h);
}

Camera::~Camera() {}

void Camera::setBounds(float w, float h)
{
	if (!(w > 1.f && h > 1.f)) return;
	// Normalize width and height
	m_width = 1.f/((w - 1.f) * 0.5f);
	m_height = 1.f/((h-1.f) * 0.5f);
}

Camera::CameraMovement Camera::getCameraMovement()
{
	return m_movement;
}

void Camera::mouseDown(const glm::vec2 point, CameraMovement movement)
{
	switch(movement)
	{
		case CameraMovement::ARC:
			m_startVector = mapToSphere(point);
			break;
		case CameraMovement::TRACK:
			m_startVector = vec3(point.x, point.y, 0.f);
			break;
		case CameraMovement::DOLLY:
			m_startVector = vec3(point.x, point.y, point.y);
			break;
		case CameraMovement::IDLE:
			break;
	}
	m_movement = movement;
}

glm::mat4 Camera::drag(const vec2 point)
{
	if (m_movement == CameraMovement::ARC)
	{
		m_releaseVector = mapToSphere(point);
		vec3 perp = cross(m_startVector, m_releaseVector);
		if (length(perp) > FLT_EPSILON)
			return mat4_cast(quat(dot(m_startVector, m_releaseVector),
						perp.x, perp.y, perp.z));
		else
			return mat4_cast(quat(0.0f, vec3(0.0f)));
	}
       	else if (m_movement == CameraMovement::TRACK)
	{
		m_releaseVector.x = (point.x - m_startVector.x) * 0.005f;
		m_releaseVector.y = -1.f * (point.y - m_startVector.y) * 0.005f;
		m_releaseVector.z = 0.0f;
		return glm::translate(mat4(1.f), m_releaseVector);
	}
	else if (m_movement == CameraMovement::DOLLY)
	{
		m_releaseVector.x = 1.0f - (point.y - m_startVector.y) * 0.005f;
		m_releaseVector.y = 1.0f - (point.y - m_startVector.y) * 0.005f;
		m_releaseVector.z = 1.0f - (point.y - m_startVector.y) * 0.005f;

		return glm::scale(mat4(1.f), m_releaseVector);
	}
	return mat4(1.f);
}

// Protected methods
vec3 Camera::mapToSphere(const vec2 point)
{
	vec2 tmp;
	float length;
	tmp = point;
	tmp.x = (tmp.x * m_width) - 1.f;
	tmp.y = 1.f - (tmp.y - m_height);
	length = (tmp.x * tmp.x) + (tmp.y * tmp.y);
	if (length > 1.f)
	{
		// point out of sphere
		float l;
		l = 1.f / glm::sqrt(length);
		return vec3(tmp.x * l, tmp.y * l, 0.0f);
	}
	else return vec3(tmp.x, tmp.y, glm::sqrt(1.0f - length));

}

