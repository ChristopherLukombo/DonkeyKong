#pragma once

#include <functional> // Defines std::function & std::bind

/*
Each enum meme is equivalent to a int, Keyboard event prevents any id(int)
clashing and make sure that anything added past this point is higher than
the absolute maximum(NO ID CLASHES)
*/

enum EventType
{
	KeyDown			= sf::Event::KeyPressed,
	KeyUp			= sf::Event::KeyReleased,
	MouseButtonDown = sf::Event::MouseButtonPressed,
	MouseButtonUp	= sf::Event::MouseButtonReleased,
	WindowResized	= sf::Event::Resized,
	GainedFocus		= sf::Event::GainedFocus,
	LostFocus		= sf::Event::LostFocus,
	MouseEntered	= sf::Event::MouseEntered,
	MouseLeft		= sf::Event::MouseLeft,
	Closed			= sf::Event::Closed,
	TextEntered		= sf::Event::TextEntered,
	Keyboard		= sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {
	EventInfo() { m_code = 0; }
	EventInfo(int l_event) { m_code = l_event; }
	union { //type défini par l’utilisateur dans lequel tous les membres partagent le même emplacement de mémoire
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
	EventDetails(const std::string& l_bindName)
		: m_name(l_bindName)
	{
		Clear();
	}

	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_keyCode; // Single key code

	void Clear() {
		m_size =			sf::Vector2i(0, 0);
		m_textEntered =		0;
		m_mouse =			sf::Vector2i(0, 0);
		m_keyCode =			-1;
	}

};

struct Binding {
	Binding(const std::string& l_name) //action we want to bind the Event to
		:m_name(l_name), m_details(l_name), c(0){}

	void BindEvent(EventType l_type, EventInfo l_info = EventInfo()) //add the type and info of the event to the vector
	{
		m_events.emplace_back(l_type, l_info);
	}

	Events m_events;
	std::string m_name;
	int c; // Count of events that are "happening".

	EventDetails m_details;
};

using Bindings = std::map<std::string, Binding*>; // one biding per action
using Callbacks = std::map<std::string, std::function<void(EventDetails*)>>; // map -> one callback per action
/*
	std::function<void(void)> foo  = std::bind(&Bar::method1, this);

	function wrapper foo which hold function with a void signature
	std:bind is used to bind Bar::method1 to the foo obj
	'this' refers the instance of the class that is having its method (member function 'method1')
	being registered as a callback

*/

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding *l_binding);
	bool RemoveBinding(std::string l_name);

	void SetFocus(const bool& l_focus)
	{
		m_hasFocus = l_focus;
	}

	//Needs to be define in the Header !
	template<class T> // We dont have to template entire class because of the std::function
	bool AddCallback(const std::string& l_name, void(T::*l_func) (EventDetails*), T* l_instance)
	{

		auto temp = std::bind(l_func, l_instance, std::placeholders::_1); // placeholder will be replace by an arguemnt in the future
		return m_callbacks.emplace(l_name, temp).second;
	}

	void RemoveCallback(const std::string& l_name) {
		m_callbacks.erase(l_name);
	}

	void HandleEvent(sf::Event& l_event);
	void Update();

	sf::Vector2i GetMousePosition(sf::RenderWindow* l_window = nullptr) {
		return (l_window ? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition());
	}

private:
	void LoadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;


};

