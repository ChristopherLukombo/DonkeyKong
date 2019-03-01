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
	mWindow.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	mWindow.display();
}

void Window::Update()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus) {
			mIsFocused = false;
			mEventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			mIsFocused = true;
			mEventManager.SetFocus(true);
		} 
		mEventManager.HandleEvent(event);
	}
	mEventManager.Update();
}

bool Window::isDone()
{
	return mIsDone;
}

bool Window::isFullscreen()
{
	return mIsFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return mWindowSize;
}

bool Window::Isfocused()
{
	return mIsFocused;
}

EventManager * Window::GetEventManager()
{
	return &mEventManager;
}

void Window::ToggleFullscreen(EventDetails* l_details)
{
	mIsFullscreen = !mIsFullscreen;
	Destroy();
	Create();
}

void Window::Close(EventDetails * l_details)
{
	mIsDone = true;
}

void Window::Draw(sf::Drawable & l_drawable)
{
	mWindow.draw(l_drawable);
}

void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	mWindowTitle = l_title;
	mWindowSize = l_size;
	mIsFullscreen = false;
	mIsDone = false;
	mIsFocused = true;
	mEventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullscreen, this);
	mEventManager.AddCallback("Window_close", &Window::Close, this);
	Create();
}

void Window::Destroy()
{
	mWindow.close();
}

void Window::Create()
{
	sf::Uint32 style = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Close) ;
	mWindow.create({ mWindowSize.x, mWindowSize.y, 32 }, mWindowTitle, style);
	mWindow.setFramerateLimit(160);
}

