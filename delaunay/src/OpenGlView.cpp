#include "OpenGlView.h"

OpenGLView::OpenGLView(int width, int height, const std::string &title)
	:glfw::Window()
{
	glfw::Window::Create(width, height, title);
	glfw::Window::MakeContextCurrent();
	glfw::FramebufferSize fb_size;
	fb_size = glfw::Window::GetFramebufferSize();
	Resize(fb_size.x, fb_size.y);

	while (!glfw::Window::ShouldClose())
	{
		glfw::Window::PollEvents();
		glfw::Event event;
		while (glfw::Window::GetEvents(event))
		{
			switch (event.type)
			{
				case glfw::Event::Type::Key:
					if (event.key.action ==
							glfw::KeyAction::Press)
						if (event.key.key ==
								glfw::Key::Escape)
							glfw::Window::SetShouldClose(GL_TRUE);

				case glfw::Event::Type::FramebufferSize:
						fb_size =
							glfw::Window::GetFramebufferSize();
						Resize(fb_size.x, fb_size.y);
			}
		}
		GLPaint();
	}
}

OpenGLView::~OpenGLView()
{
}

void OpenGLView::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	m_aspect_ratio = width / (float) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(GLdouble)width / 2,
			(GLdouble)width / 2,
			-(GLdouble)height / 2,
			(GLdouble) height / 2, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLView::GLPaint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.f, 0.f, 0.f);
		glVertex2f(50.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex2f(-50.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex2f(0.f, 50.f);
	}
	glEnd();
	glfw::Window::SwapBuffers();
}

World& OpenGLView::get_world()
{
	return m_world;
}
