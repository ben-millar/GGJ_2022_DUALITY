#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "InputInterface.h"

class KeyboardInput : public InputInterface
{
public:
	KeyboardInput();
	~KeyboardInput() = default;

	/// <summary>
	/// @brief Recieve and abstract SDL events into InputEvents
	/// </summary>
	/// <param name="t_event"></param>
	void handleInput(sf::Event t_event);

private:

	/// <summary>
	/// @Brief Initialise the K/V pairs in our map
	/// </summary>
	void initialiseMap();

	// A mapping of SDL input to our generic input struct
	std::unordered_map<sf::Keyboard::Key, InputID> m_mapping;

	bool m_keyRepeatEnabled{ false };

};

#endif // !KEYBOARD_INPUT_H