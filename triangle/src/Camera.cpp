/**
 * Camera
 *
 * File: 	Camera.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 6 2015
 */

#include "Camera.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

std::ostream& operator<< (std::ostream& o, const vec3 &v)
{
	o << '[' << v.x << ", " << v.y << ", " << v.z << ']';
	return o;
}

std::ostream& operator<< (std::ostream& o, const vec4 &v)
{
	o << '[' << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ']';
	return o;
}

Camera::Camera()
{
	m_View_good = false;
	m_Persp_good = false;
	m_VP_good = false;
	m_fov = 45.f;
	m_position = vec3(2.f, 2.f, 1.f);
	m_direction= vec3(0.f, 0.f, 0.f);
	m_updir = vec3(0.f, 1.f, 0.f);
	m_rotate_distance = length(m_direction - m_position);
}


// Must be called in a matrix
void Camera::Render()
{

	if (!m_View_good)
	{
		m_View = lookAt(m_position, m_direction, m_updir);
		m_VP_good = false;
		m_View_good = true;
	}

	if (!m_Persp_good)
	{
		m_Persp = perspective(m_fov, (float)m_width/m_height,
			       	0.1f, 1024.f);
		m_VP_good = false;
		m_Persp_good = true;
	}

	if (!m_VP_good)
	{
		m_VP = m_Persp * m_View;
		m_VP_good = true;
	}
	glMultMatrixf(&m_VP[0][0]);
}

void Camera::move_camera(vec3 direction)
{
	m_View_good = false;
	m_position += direction;
	m_rotate_distance = length(m_direction - m_position);
}

void Camera::set_view(vec3 position)
{
	m_View_good = false;
	m_direction = position;
	m_rotate_distance = length(m_direction - m_position);
}

void Camera::place_camera(vec3 position)
{
	m_View_good = false;
	m_position = position;

}

void Camera::rotate_x(GLfloat angle)
{
	m_View_good = false;
}

void Camera::rotate_y(GLfloat angle)
{
	m_View_good = false;
}

void Camera::rotate_z(GLfloat angle)
{
	m_View_good = false;
}

void Camera::move_forward(GLfloat distance)
{
	m_View_good = false;
}

void Camera::strafe_right(GLfloat distance)
{
	m_View_good = false;
	vec3 direction = normalize(m_direction - m_position);
	vec3 right_vec = cross(direction, m_updir) * distance;
	m_position += right_vec; m_direction += right_vec;
	m_direction = normalize(m_direction - m_position) * m_rotate_distance + m_position;
}

void Camera::strafe_up(GLfloat distance)
{
	m_View_good = false;
	vec3 direction = normalize(m_direction - m_position);
	vec3 right_vec = normalize(cross(m_updir, direction));
	vec3 up = cross(direction, right_vec) * distance;
	m_position += up; m_direction += up;
	m_direction = normalize(m_direction - m_position) * m_rotate_distance + m_position;
}

void Camera::dolly_in(GLfloat distance)
{
	glm::vec3 direction = glm::normalize(View() - Position());
	move_camera(direction * distance);
	m_rotate_distance = glm::length(m_position - m_direction);
#ifdef DEBUG
	std::cout << "Rotation Distance: " << m_rotate_distance << '\n';
#endif
	if (m_rotate_distance < 1.f)
	{
		set_view(View() + (direction * distance));
	}
}

void Camera::rotate_horizontal(GLfloat distance)
{
	m_View_good = false;
	vec3 direction = normalize(m_direction - m_position);
	vec3 right_vec = cross(direction, m_updir) * distance;
	m_position += right_vec;
	m_direction = normalize(m_direction - m_position) * m_rotate_distance
		+ m_position;
}

void Camera::rotate_vertical(GLfloat distance)
{
	m_View_good = false;
	vec3 direction = normalize(m_direction - m_position);
	vec3 right_vec = normalize(cross(direction, m_updir));
	vec3 up = normalize(cross(direction, right_vec));
	m_position += up * distance;
	m_position = normalize(m_position - m_direction) * m_rotate_distance + m_direction;
}

void Camera::set_fov(GLfloat fov)
{
	m_Persp_good = false;
	m_fov = fov;
}

void Camera::adjust_fov(GLfloat delta)
{
	if (m_fov + delta < C_MAX_FOV && m_fov + delta > C_MIN_FOV)
	{
		m_Persp_good = false;
		m_fov += delta;
	}
}

void Camera::set_bounds(GLint width, GLint height)
{
	m_Persp_good = false;
	glViewport(0, 0, width, height);
	m_width = width;
	m_height = height;
}
