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
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		} 
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
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

bool Window::Isfocused()
{
	return m_isFocused;
}

EventManager * Window::GetEventManager()
{
	return &m_eventManager;
}

void Window::ToggleFullscreen(EventDetails* l_details)
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Close(EventDetails * l_details)
{
	m_isDone = true;
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
	m_isFocused = true;
	m_eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullscreen, this);
	m_eventManager.AddCallback("Window_close", &Window::Close, this);
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

