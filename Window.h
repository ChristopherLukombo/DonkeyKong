#pragma once
#include "EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw(); // Clear the window
	void EndDraw(); // Display the change

	void Update();

	bool isDone();
	bool isFullscreen();
	sf::Vector2u GetWindowSize();
	sf::RenderWindow* GetRenderWindow() { return &mWindow; }

	bool Isfocused();
	void SetFocus(const bool &focus) { mIsFocused = focus; };
	EventManager* GetEventManager();
	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details = nullptr);

	void Draw(sf::Drawable& l_drawable);


private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();

	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;
	std::string mWindowTitle;
	EventManager mEventManager;
	bool mIsFocused;
	bool mIsDone;
	bool mIsFullscreen;
};

