#include "OpenGlView.h"

OpenGlView::OpenGlView(int width, int height, const std::string& title)
	:glfw::Window()
{
	/*m_world = NULL;
	m_initial_width = m_width = width;
	m_initial_height = m_height = height;
	m_title = title;

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
	} */
}


OpenGlView::OpenGlView(int width, int height, const std::string& title,
		World* world)
	:glfw::Window()
{
	m_world = world;
	m_initial_width = m_width = width;
	m_initial_height = m_height = height;
	m_title = title;

	initialize();
	terminate();



	/*while (1)
	{
	} */

	/*
	m_world = world;
	m_initial_width = m_width = width;
	m_initial_height = m_height = height;
	m_title = title;

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
	} */
}

OpenGlView::~OpenGlView()
{
}


void OpenGlView::Resize(int width, int height)
{
	std::cerr << "Resize called\n";
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
	m_b_redraw = true;
	m_cv_redraw.notify_all();
}

const World* OpenGlView::get_world() const
{
	return m_world;
}

void OpenGlView::set_world(const World& w)
{
//	if (m_world) delete m_world;
// 	std::cerr << "World Polygons " << m_world.polygons() << '\n';
}


void OpenGlView::initialize()
{
	glfw::Window::Create(m_width, m_height, m_title);
	glfw::Event event;
	m_b_kill = false;

	// Initialize rendering thread
	thread_redraw = std::thread(&OpenGlView::t_redraw, this);

	for(;;)
	{
		GLPaint();
		if (glfw::Window::ShouldClose())
			break;

		glfw::Window::PollEvents();
		while (glfw::Window::GetEvents(event))
		{
			switch(event.type)
			{
				case glfw::Event::Type::Key:
					if (event.key.action ==
							glfw::KeyAction::Press)
					{
						if (event.key.key ==
								glfw::Key::Escape)
							glfw::Window::SetShouldClose(GL_TRUE);
					}

				case glfw::Event::Type::FramebufferSize:
					m_b_resize = true;

			}
		}
	}
	m_b_kill = true;
}

void OpenGlView::terminate()
{
	thread_redraw.join();
}

/*
 * Threads
 */
/*!\brief Redraw Method */
void OpenGlView::t_redraw()
{
	// Only redraw if the redraw has been set
	std::unique_lock<std::mutex> sleep_lock(m_redraw);
	glfw::Window::MakeContextCurrent();
	glfw::FramebufferSize fb_size;
	fb_size = glfw::Window::GetFramebufferSize();
	Resize(fb_size.x, fb_size.y);

	if (m_world == NULL) return;
	while (!m_b_kill)
	{

		// Resize
		if (m_b_resize)
		{
			fb_size = glfw::Window::GetFramebufferSize();
			Resize(fb_size.x, fb_size.y);
			m_b_resize = false;
		}
		for(;;)
		{
			m_mb_redraw.lock();
			bool redraw = m_b_redraw;
			m_mb_redraw.unlock();
			if (redraw) break; // If we need to redraw, break
			m_cv_redraw.wait(sleep_lock); // Otherwise sleep
			if (m_b_kill) break;
		}
		if (m_b_kill) break; // If we need to die, leave now!
		// Otherwise, we need to go ahead and redraw

		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		m_world->draw();


		glfw::Window::SwapBuffers();

		m_mb_redraw.lock();
		m_b_redraw = false;
		m_mb_redraw.unlock();
	}
}
