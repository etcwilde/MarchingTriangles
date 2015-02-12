#include "Camera.hpp"

Camera::Camera()
{

	m_position = vec3(0.f, 0.f, 0.f);
	m_direction = vec3(0.f, 0.f, -1.f);
	m_right = vec3(1.f, 0.f, 0.f);
	m_rotateX = m_rotateY = m_rotateZ = 0;

	m_ortho = false;
	m_fov = 45.f;
}

void Camera::Render()
{
	raw_render();
}

void Camera::move_camera(vec3 direction)
{
	raw_move_camera(direction);
}

void Camera::set_view(vec3 position)
{
	//TODO: Possibly better way to do this
	vec3 d_norm = normalize(m_direction);
	vec3 p_norm = normalize(m_position);
	GLfloat angle = acos(dot(d_norm, p_norm));
	if (abs(angle) < FLT_EPSILON) return;
	vec3 axis = d_norm;
	axis = cross(axis, p_norm);
	rotate_x(axis[0] * angle * 180 / M_PI);
	rotate_y(axis[1] * angle * 180 / M_PI);
	rotate_z(axis[2] * angle * 180 / M_PI);
}

void Camera::place_camera(vec3 position)
{
	raw_place_camera(position);
}

void Camera::rotate_x(GLfloat angle)
{
	raw_rotateX(angle);
}

void Camera::rotate_y(GLfloat angle)
{
	raw_rotateY(angle);
}

void Camera::rotate_z(GLfloat angle)
{
	raw_rotateZ(angle);
}

void Camera::move_forward(GLfloat distance)
{
	raw_move_forward(distance);
}

void Camera::strafe_right(GLfloat distance)
{
	raw_strafe_right(distance);
}

void Camera::strafe_up(GLfloat distance)
{
	raw_strafe_up(distance);
}

void Camera::set_fov(GLfloat fov)
{
	m_fov = fov;
}


void Camera::adjust_fov(GLfloat delta)
{
	m_fov += delta;
}

/**
 * Private Method Definitions
 */

#include <GL/gl.h>
#include <GL/glu.h>

void Camera::raw_render()
{
	vec3 viewpoint = m_position + m_direction;
	glLoadIdentity();
	gluLookAt(m_position[0], m_position[1], m_position[2],
			m_direction[0], m_direction[1], m_direction[2],
			m_updir[0], m_updir[1], m_updir[2]);

}

void Camera::raw_move_camera(vec3 direction)
{
	m_position += direction;
}

void Camera::raw_place_camera(vec3 position)
{
	m_position = position;
}

#include <math.h>
void Camera::raw_rotateX(GLfloat angle)
{
	m_rotateX += angle;
	m_direction = m_direction * cos(angle * M_PI180) + m_updir *
		sin(angle * M_PI180);
	m_direction = normalize(m_direction);
	m_updir = -cross(m_direction, m_right);
}

void Camera::raw_rotateY(GLfloat angle)
{
	m_rotateY += angle;
	m_direction = m_direction * cos(angle * M_PI180) - m_right *
		sin(angle * M_PI180);
	m_direction = normalize(m_direction);
	m_right = cross(m_direction, m_updir);
}

void Camera::raw_rotateZ(GLfloat angle)
{
	m_rotateZ += angle;
	m_right = m_right * cos(angle * M_PI180) - m_right * sin(angle * M_PI180);
	m_right = normalize(m_right);
	m_updir = -cross(m_direction, m_right);
}

void Camera::raw_move_forward(GLfloat distance)
{
	m_position += (m_direction * -distance);
}

void Camera::raw_strafe_right(GLfloat distance)
{
	m_position += (m_right * distance);
}

void Camera::raw_strafe_up(GLfloat distance)
{
	m_position += (m_updir * distance);
} 
