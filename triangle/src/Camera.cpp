#include "Camera.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera()
{
}


// Must be called in a matrix
void Camera::Render()
{

	mat4 Projection = perspective(45.f, 16.f/9.f, 0.1f, 1024.f);
	mat4 View = glm::lookAt(vec3(2, 0.5, 1), vec3(0.0, 1.1, 0.0), vec3(0, 1, 0));
	//mat4 View = View * Projection;
	//mat4 VP = View * Projection;
	mat4 VP = Projection * View;

	glMultMatrixf(&VP[0][0]);

}

void Camera::move_camera(vec3 direction)
{
}

void Camera::set_view(vec3 position)
{
}

void Camera::place_camera(vec3 position)
{
}

void Camera::rotate_x(GLfloat angle)
{
}

void Camera::rotate_y(GLfloat angle)
{
}

void Camera::rotate_z(GLfloat angle)
{
}

void Camera::move_forward(GLfloat distance)
{
}

void Camera::strafe_right(GLfloat distance)
{
}

void Camera::strafe_up(GLfloat distance)
{
}

void Camera::set_fov(GLfloat fov)
{
}


void Camera::adjust_fov(GLfloat delta)
{
}

/**
 * Private Method Definitions
 */



