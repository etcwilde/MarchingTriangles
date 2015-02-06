#include "World.hpp"

World::World()
	: m_drawGrid(true)
{}

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

void World::keyPressEvent(GLFWwindow* w, int key, int scancode, int mods)
{
	std::cout << "Key press: " << key << ", " << scancode << '\n';
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

void World::Draw()
{
	draw_coordinates();
}

void World::draw_coordinates()
{

	if (m_drawGrid)
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
	}
}
