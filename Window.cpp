#include "pch.h"
#include "Window.h"


Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string & l_title, const sf::Vector2u & l_size)
{
	Setup(l_title, l_size);
}


Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();
		}
	}
}

bool Window::isDone()
{
	return m_isDone;
}

bool Window::isFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	sf::Uint32 style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Close) ;
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	m_window.setFramerateLimit(160);
}

