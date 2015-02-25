/**
 * World
 *
 * File: 	World.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 6 2015
 */

#include "World.hpp"

#include <GL/gl.h>

#include "ImplicitTorus.hpp"

// Hahahahahahaha -- this is dumb
std::list<glm::vec3> dumb_find(Implicit::Torus* obj, const glm::vec3& v, unsigned int trials)
{
	float value = 1.f;
	double range = 0.001e-5;
	float t_x, t_y, t_z;
	std::list<glm::vec3> ret_list;

	while (trials)
	{
		t_x = v.x + range * (rand() - 0.5f);
		t_y = v.y + range * (rand() - 0.5f);
		t_z = v.z + range * (rand() - 0.5f);
		if (obj->touches(glm::vec3(t_x, t_y, t_z), 0.1))
			ret_list.push_back(glm::vec3(t_x, t_y, t_z));
		range *= 1.000005f;
		trials--;
	}
	return ret_list;
}

World::World()
	: m_drawGrid(true)
{
	m_background_color = glm::vec3(.0, .1, .1);
	m_grid_color = glm::vec3(1, 1, 1);
	initGL();

	// Do a thing with a sphere
	Implicit::Sphere test_sphere(geoffFunction, 10);

	//Implicit::Cube test_cube(geoffFunction, 1, 5);
	//
	Implicit::Torus test_torus(geoffFunction, 2, 4);

	m_point_cloud = dumb_find(&test_torus, glm::vec3(-10, -10, -10), 1000000);
	std::cout << "Points hit: " << m_point_cloud.size() << '\n';


	//m_point_cloud = dumb_find(&test_cube, glm::vec3(-10, -10, -10), 1000000);
	//m_point_cloud = dumb_find(&another_obj , glm::vec3(-10, -10, -10), 10000);



	/*for (std::list<glm::vec3>::iterator it = m_point_cloud.begin();
			it != m_point_cloud.end(); it++)
	{
		std::cout << (*it).x << ", "
			<< (*it).y << ", "
			<< (*it).z << '\n';
	}*/
}

void World::initGL()
{
	glClearColor(m_background_color[0], m_background_color[1],
			m_background_color[2], 1.f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(5.0f);
	m_camera.set_bounds(1, 1);

	glPointSize(10.f);
}

World::~World()
{
}

World& World::getWorldInstance()
{
	static World instance;
	return instance;
}

void World::mousePressEvent(GLFWwindow* w, int button, int mods)
{
	m_mouseDrag = true;
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			if ((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
				m_cam_mode = CAM_STRAFE;
			break;
	}
}

void World::mouseReleaseEvent(GLFWwindow* w, int button, int mods)
{
	m_mouseDrag = false;
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			// release camera mode
			m_cam_mode = CAM_ROTATE;
			break;
	}
}

void World::mouseClickEvent(GLFWwindow* w, int button, int action, int mods)
{
	/*
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && mods == GLFW_MOD_ALT)
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(w, &x, &y);
			m_mouseDrag = true;
			m_lastRotation = m_currentRotation;
			m_camera.mouseDown(glm::vec2(x, y), Camera::CameraMovements::TUMBLE);
		}
		else m_mouseDrag = false;
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && mods == GLFW_MOD_SHIFT)
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(w, &x, &y);
			m_mouseDrag = true;
			m_lastTranslate = m_currentTranslate;
			m_camera.mouseDown(glm::vec2(x, y), Camera::CameraMovements::TRACK);
		}
		else m_mouseDrag = false;
		return;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && mods == GLFW_MOD_CONTROL)
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(w, &x, &y);
			m_mouseDrag = true;
			m_lastScale = m_currentScale;
			m_camera.mouseDown(glm::vec2(x, y), Camera::CameraMovements::DOLLY);
		}
		else m_mouseDrag = false;
		return;
	} */
}

void World::mouseMoveEvent(GLFWwindow* w, double x, double y)
{
	if (!m_mouseDrag) m_old_mouse = vec2(x, y); // Expensive
	if (m_mouseDrag)
	{
		if (m_cam_mode ==  CAM_STRAFE) camera_strafe(vec2(x, y));
		else camera_rotate(vec2(x, y));
	}
}

void World::scrollEvent(GLFWwindow* w, double delta_x, double delta_y)
{
	// Nothing yet
	camera_dolly(delta_x, delta_y);
}

void World::keyPressEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	// Increment or decrement fov
	if (key == GLFW_KEY_I)
	{
		m_camera.adjust_fov(.1);
	}
	else if (key == GLFW_KEY_J)
	{
		m_camera.adjust_fov(-.1);
	}
	if (key == GLFW_KEY_LEFT_SHIFT) m_small_increments = true;
}

void World::keyHoldEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	// Increment or decrement fov
	if (key == GLFW_KEY_I)
	{
		m_camera.adjust_fov(.1);
	}
	else if (key == GLFW_KEY_J)
	{
		m_camera.adjust_fov(-.1);
	}

}

void World::keyReleaseEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	if (key == GLFW_KEY_LEFT_SHIFT) m_small_increments = false;
}

void World::resizeEvent(GLFWwindow *w, int width, int height)
{
	m_camera.set_bounds(width, height);
}

void World::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	m_camera.Render();
	draw_coordinates();

	glBegin(GL_POINTS);
	for (std::list<glm::vec3>::iterator it = m_point_cloud.begin();
			it != m_point_cloud.end(); it++)
	{
		/*std::cout << (*it).x << ", "
			<< (*it).y << ", "
			<< (*it).z << '\n';*/
		glVertex3f((*it).x, (*it).y, (*it).z);

//1.64494e+10
	}
	glEnd();

	glPopMatrix();
}

void World::draw_coordinates()
{
	glColor3f(m_grid_color[0], m_grid_color[1], m_grid_color[2]);
	glBegin(GL_LINES);
	for (int i = 0; i < 25; ++i)
	{
		glVertex3f((-12.0f + i), 0.0f, -12.0f);
		glVertex3f((-12.0f + i), 0.0f, 12.0f);

		glVertex3f(-12.0f, 0.0f, (-12.0f + i));
		glVertex3f(12.0f, 0.0f, (-12.0f + i));
	}
	glEnd();

	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 25, 0);
	glVertex3f(0, -25, 0);
	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 50);
	glVertex3f(0, 0, -50);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(50, 0, 0);
	glVertex3f(-50, 0, 0);
	glEnd();


	/*
	// Build vertex buffer
	GLint the_grid[] =
	{
		20,  	0,	20,	//0
		-20, 	0, 	20, 	//1
		20,  	0,	-20,	//2
		-20, 	0, 	-20,	//3
		20,  	0,	15,	//4
		-20, 	0, 	15, 	//5
		20,  	0,	10, 	//6
		-20, 	0, 	10,	//7
		20,  	0,	5, 	//8
		-20, 	0, 	5, 	//9
		20,  	0,	0,	//10
		-20, 	0, 	0,  	//11
		20,  	0,	-5,	//12
		-20, 	0, 	-5,	//13
		20,  	0,	-10,	//14
		-20, 	0, 	-10,	//15
		20,  	0,	-15,	//16
		-20, 	0, 	-15,	//17

		15, 	0,	20,	//18
		15, 	0,	-20,	//19
		10, 	0,	20,	//20
		10,	0,	-20,	//21
		5,  	0,	20,	//22
		5,  	0,	-20,	//23
		0,  	0,	20,	//24
		0,  	0,	-20,	//25
		-5, 	0,	20,	//26
		-5, 	0,	-20,	//27
		-10,	0,	20,	//28
		-10,	0,	-20,	//29
		-15,	0,	20,	//30
		-15,	0,	-20	//31
	};
	GLubyte grid_index[]
	{
		0,	1,
		4,	5,
		6,	7,
		8,	9,
		10,	11,
		12,	13,
		14,	15,
		16,	17,
		2,	3,
		18,	19,
		20,	21,
		22,	23,
		24,	25,
		26,	27,
		28,	29,
		30,	31,
		1,	3,
		0,	2
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3ub(m_grid_color[0], m_grid_color[1], m_grid_color[2]);
	glVertexPointer(3, GL_INT, 0, the_grid);
	glDrawElements(GL_LINES, 18, GL_UNSIGNED_BYTE, grid_index);
	glDisableClientState(GL_VERTEX_ARRAY);

	*/
}

void World::camera_dolly(double x, double y)
{
	if (m_small_increments)
	{
		x /= 10;
		y /= 10;
	}
	glm::vec3 direction = m_camera.View() - m_camera.Position();
	direction = glm::normalize(direction);
	m_camera.move_camera(direction * (GLfloat)y);
	m_camera.set_view(m_camera.View() +(direction * (GLfloat)y));
}

void World::camera_strafe(vec2 mouse_point)
{
	float x_strafe = mouse_point.x - m_old_mouse.x;
	float y_strafe = mouse_point.y - m_old_mouse.y;

	if (m_small_increments)
	{
		x_strafe /= 10;
		y_strafe /= 10;
	}
	m_camera.strafe_right(-x_strafe / m_camera.Fov());
	m_camera.strafe_up(y_strafe / m_camera.Fov());
	m_old_mouse = mouse_point;

}

void World::camera_rotate(vec2 mouse_point)
{
	float x_rotate = (mouse_point.x - m_old_mouse.x) / 100;
	float y_rotate = (mouse_point.y - m_old_mouse.y) / 100;
	if (m_small_increments)
	{
		x_rotate /= 10;
		y_rotate /= 10;
	}
	m_camera.rotate_horizontal(x_rotate);
	m_camera.rotate_vertical(y_rotate);
	m_old_mouse = mouse_point;
}
