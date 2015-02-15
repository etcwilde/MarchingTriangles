#include "Camera.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera()
{
	m_View_good = false;
	m_Persp_good = false;
	m_VP_good = false;
	m_fov = 45.f;

	m_position = vec3(2.f, 2.f, 1.f);
	m_direction= vec3(0.f, 1.1f, 0.f);
	m_updir = vec3(0.f, 1.f, 0.f);
}


// Must be called in a matrix
void Camera::Render()
{
	if (!m_View_good)
	{
		m_View = glm::lookAt(m_position, m_direction, m_updir);
		m_VP_good = false;
		m_View_good = true;
	}

	if (!m_Persp_good)
	{
		m_Persp = perspective(m_fov, (float)m_width/m_height, 0.1f, 1024.f);
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
}

void Camera::set_view(vec3 position)
{
	m_View_good = false;
	m_direction = position;
}

void Camera::place_camera(vec3 position)
{
	m_View_good = false;

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
}

void Camera::strafe_up(GLfloat distance)
{
	m_View_good = false;
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

/**
 * Private Method Definitions
 */



