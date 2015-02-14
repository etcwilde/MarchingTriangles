#include "World.hpp"

#include <GL/gl.h>

World::World()
	: m_drawGrid(true)
{
	m_background_color = glm::vec3(0, 0, 5);
	m_grid_color = glm::vec3(1, 1, 1);

	// Initialize gl
	glClearColor(m_background_color[0], m_background_color[1],
			m_background_color[2], 1.f);
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
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "Left pressed\n";
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "Right pressed\n";
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "Middle pressed\n";
			break;
	}
}

void World::mouseReleaseEvent(GLFWwindow* w, int button, int mods)
{
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "Left released\n";
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "Right released\n";
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "Middle released\n";
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

	/*if (m_mouseDrag)
	{
		glm::mat4 transform = m_camera.drag(glm::vec2(x, y));
		switch(m_camera.getCameraMovement())
		{
			case Camera::CameraMovements::TUMBLE:
				m_currentRotation = transform * m_lastRotation;
				break;
			case Camera::CameraMovements::TRACK:
				m_currentTranslate = transform * m_lastTranslate;
				break;
			case Camera::CameraMovements::DOLLY:
				m_currentScale = transform * m_lastScale;
				break;
		}
	} */
}

void World::scrollEvent(GLFWwindow* w, double delta_x, double deta_y)
{
	// Nothing yet
	std::cout << "scroll\n";
}

void World::keyPressEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	//std::cout << "Key press: " << key << ", " << scancode << '\n';
	glm::vec3 cam_pos = m_camera.Position();
	std::cout << "Camera position: " << cam_pos[0] << ", " << cam_pos[1]
		<< ", "<< cam_pos[2] <<'\n';
	cam_pos = m_camera.View();
	std::cout << "Camera Direction: " << cam_pos[0] << ", " << cam_pos[1]
		<< ", "<< cam_pos[2] <<'\n';

}

void World::keyHoldEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	// nothing
	std::cout << "Key hold: " << key << ", " << scancode << '\n';
}

void World::keyReleaseEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	std::cout << "Key release: " << key << ", " << scancode << '\n';
}

void World::resizeEvent(GLFWwindow *w, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (double)width/height, 1.0f, 1024.0f);
	//m_camera.setBounds((float)width, (float)height);
}

void World::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	m_camera.Render();
	glMatrixMode(GL_MODELVIEW);
	draw_coordinates();
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
	glVertex3f(0, 100, 0);
	glVertex3f(0, -100, 0);
	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 100);
	glVertex3f(0, 0, -100);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(100, 0, 0);
	glVertex3f(-100, 0, 0);
	glEnd();

	/*if (m_drawGrid)
	{
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
		glColor3ub(48, 48, 48);
		glVertexPointer(3, GL_INT, 0, the_grid);
		glDrawElements(GL_LINES, 18, GL_UNSIGNED_BYTE, grid_index);
		glDisableClientState(GL_VERTEX_ARRAY);
	} */


}
