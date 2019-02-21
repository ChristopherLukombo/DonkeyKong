#include "pch.h"
#include "EventManager.h"


EventManager::EventManager() : m_hasFocus(true) 
{
	LoadBindings();
}


EventManager::~EventManager()
{
	for (auto &itr : m_bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding * l_binding)
{
	if ( m_bindings.find(l_binding->m_name) !=  m_bindings.end() )
	{
		return false;
	}

	return m_bindings.emplace(l_binding->m_name, l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name)
{
	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end()) 
	{
		return false;
	}
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::HandleEvent(sf::Event & l_event)
{
	// Handling SFML EVENTS

	for (auto &b_itr : m_bindings) // bindings iterator
	{
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events ) // events iterator
		{
			EventType sfmlEvent = (EventType)l_event.type;

			if (e_itr.first != sfmlEvent) {
				continue;
			}

			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp )
			{
				if (e_itr.second.m_code == l_event.key.code) {
					//Matching event with the Key
					//Increase count of happening event
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			} 
			else if (sfmlEvent == EventType::MouseButtonDown || sfmlEvent == EventType::MouseButtonUp)
			{
				if (e_itr.second.m_code == l_event.mouseButton.button) {
					// Event Matching mouse click
					// Increase count of happening event
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;

					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else
			{
				// No need for additionanal checking.
				if (sfmlEvent == EventType::WindowResized) {
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_details.m_textEntered = l_event.text.unicode;
				}
				++(bind->c);
			}
		}

	}
}

void EventManager::Update()
{
	if (!m_hasFocus) { return; }
	//Iteration over all the bindings and their events
	for (auto &b_itr : m_bindings) 
	{
		Binding* bind = b_itr.second; // each bindings is one action
		for (auto &e_itr : bind->m_events)
		{
			switch (e_itr.first)	
			{
			case(EventType::Keyboard ) : //Checking Keybord events 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c); // incrementing the count of happening events
				}
				break;
			case(EventType::Mouse) :   // Checking Mouse Events
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c); // incrementing the count of happening events
				}
				break;
			}
		}

		// checking if happening events match the events in the container
		if (bind->m_events.size() == bind->c) {
			auto callItr = m_callbacks.find(bind->m_name); // search for the callback we registered with that event name
			if (callItr != m_callbacks.end()) {
				callItr->second(&bind->m_details); // calling the callback function we have registered with all the event details
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}

}

void EventManager::LoadBindings()
{
	//Each line is a new binding

	std::string delimiter = ":";
	std::ifstream bindings ("key_bindings.cfg", std::ifstream::in); // file open for reading
	if (!bindings.is_open())
	{
		std::cout << " FAILED TO LOAD THE key_bindings.cfg CONFIGURATION FILE." << std::endl;
		return;
	}
	else {
		std::cout << " LOADED" << std::endl;
	}
	std::string line; //  line format is : Event_name 1:1 2:3 
	
	while (std::getline(bindings, line)) // reading the file line by line
	{
		std::stringstream keystream(line); //buffer to operate on strings
		std::string callbackName;
		keystream >> callbackName; // getting the character chain before the next space
		Binding* bind = new Binding(callbackName); // store the name of the callback
		while (!keystream.eof()) // Read until the end of the line
		{
			std::string keyval;
			keystream >> keyval; // key:value of the callback
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { // if the delimiter is not found (end == the largest string value possible) skip the line
				delete bind;
				bind = nullptr;
				break;
			}
			
			EventType type = EventType(stoi(keyval.substr(start, end - start))); // getting the conresponding eventType from the key part of the key value
			int code = stoi(keyval.substr(end + delimiter.length(),	keyval.find(delimiter, end + delimiter.length()))); // getting the conresponding code from the value part of the key value
			EventInfo eventInfo;
			eventInfo.m_code = code;

			bind->BindEvent(type, eventInfo); // add the type and the code of the event to the m_events vector

		}

		if (!AddBinding(bind)) { delete bind; } // if the last binding was added, the 'bind' gets deleted
		bind = nullptr;

	}
	bindings.close();
}
