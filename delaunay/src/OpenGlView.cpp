#include "OpenGlView.h"

OpenGlView::OpenGlView(int width, int height, const std::string& title)
	:glfw::Window()
{
	m_initial_width = m_width = width;
	m_initial_height = m_height = height;
	m_title = title;


	/*glfw::Window::Create(width, height, title);
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
	} */
}

OpenGlView::~OpenGlView()
{
}


void OpenGlView::open()
{
	glfw::Window::Create(m_width, m_height, m_title);
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

void OpenGlView::Resize(int width, int height)
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

void OpenGlView::GLPaint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	m_world.draw();
	glfw::Window::SwapBuffers();
}

World& OpenGlView::get_world()
{
	return m_world;
}

void OpenGlView::set_world(World w)
{
	m_world = w;
	std::cerr << "World Polygons " << m_world.polygons() << '\n';
}


