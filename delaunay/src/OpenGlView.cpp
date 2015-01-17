#include "OpenGlView.h"

OpenGLView::OpenGLView(int width, int height, const std::string &title)
	:glfw::Window()
{
	glfw::Window::Create(width, height, title);
	glfw::Window::MakeContextCurrent();
	m_fb_size = glfw::Window::GetFramebufferSize();
	m_aspect_ratio = m_fb_size.x / (float)m_fb_size.y;

	while (!glfw::Window::ShouldClose())
	{
		glfw::Window::PollEvents();
		glfw::Event event;
		while (glfw::Window::GetEvents(event))
		{
			switch (event.type)
			{
				case glfw::Event::Type::Key:
					if (event.key.action == glfw::KeyAction::Press)
						if (event.key.key == glfw::Key::Escape)
							glfw::Window::SetShouldClose(GL_TRUE);

				case glfw::Event::Type::FramebufferSize:
					{
						glfw::WindowSize w_size =
							glfw::Window::GetSize();
						Resize(w_size.x, w_size.y);
					}
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
	std::cout << "Size\n";
	glViewport(0, 0, width, height);
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
		glVertex2f(1.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex2f(-1.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex2f(0.f, 1.f);
	}
	glEnd();
	glfw::Window::SwapBuffers();
}
