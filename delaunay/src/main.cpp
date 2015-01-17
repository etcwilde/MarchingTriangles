#include <iostream>
#include "OpenGlView.h"
#include "vector.h"

int main(int argc, char** argv)
{
	OpenGLView window(640, 480, "Window");

/*	glfw::Window window;
	window.Create(640, 480, "Window");
	window.MakeContextCurrent();
	glfw::FramebufferSize fb_size = window.GetFramebufferSize();
	float ratio = fb_size.x /(float) fb_size.y;
	glViewport(0, 0, fb_size.x, fb_size.y);
	glClear(GL_COLOR_BUFFER_BIT);
	while(!window.ShouldClose())
	{
		window.PollEvents();
		glfw::Event event;
		while(window.GetEvents(event))
		{
			switch(event.type)
			{
				case glfw::Event::Type::Key:
					if(event.key.action == glfw::KeyAction::Press)
						if(event.key.key == glfw::Key::Escape)
							window.SetShouldClose(GL_TRUE);

				case glfw::Event::Type::FramebufferSize:
					{fb_size = window.GetFramebufferSize();
					ratio = fb_size.x, fb_size.y;
					glViewport(0, 0, fb_size.x, fb_size.y);
					}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef(glfw::Time::Get() * 45.f, 0.f, 0.f, 1.f);

		glBegin(GL_TRIANGLES);
		{
			glColor3f(1.f, 0.f, 0.f);
			glVertex2f(1.f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex2f(-1.f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex2f(0.f, 1.f);
		}
		glEnd();
		window.SwapBuffers();
		window.PollEvents();
	} */
	return 0;
}
