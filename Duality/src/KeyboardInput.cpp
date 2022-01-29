#include "KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
	initialiseMap();
}

///////////////////////////////////////////////////////////////

void KeyboardInput::initialiseMap()
{
	using namespace sf;

	m_mapping.emplace(Keyboard::Up,		InputID::JUMP);
	m_mapping.emplace(Keyboard::W,		InputID::JUMP);
	m_mapping.emplace(Keyboard::Down,	InputID::DOWN);
	m_mapping.emplace(Keyboard::S,		InputID::DOWN);
	m_mapping.emplace(Keyboard::Left,	InputID::LEFT);
	m_mapping.emplace(Keyboard::A,		InputID::LEFT);
	m_mapping.emplace(Keyboard::Right,	InputID::RIGHT);
	m_mapping.emplace(Keyboard::D,		InputID::RIGHT);
	m_mapping.emplace(Keyboard::Escape,	InputID::EXIT);
}

///////////////////////////////////////////////////////////////

void KeyboardInput::handleInput(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type ||
		sf::Event::KeyReleased == t_event.type)
	{
		auto it = m_mapping.find(t_event.key.code);

		if (m_mapping.end() != it)
		{
			InputEvent e;

			// Set input ID
			e.ID = it->second;

			// Set Input Type
			e.type = (sf::Event::KeyPressed == t_event.type)
				? InputType::PRESSED
				: InputType::RELEASED;

			// Send our input notification
			notify(e);
		}
	}
}