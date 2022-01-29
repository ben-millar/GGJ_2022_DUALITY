#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

#include <set>
#include "InputHandler.h"

// This class should be overridden for each input ID we add
// E.g. MouseAndKeyboard, XboxController etc.
// It's job is to act as an abstraction layer, and to notify some generic input handler

class InputInterface
{
public:
	virtual ~InputInterface() {};

	/// <summary>
	/// @brief Adds an input handler to our interface to process input recieved
	/// </summary>
	/// <param name="t_handler">Pointer to an input handler</param>
	void addHandler(InputHandler* t_handler);

	/// <summary>
	/// @brief Removes a given input handler if it's registered with us
	/// </summary>
	/// <param name="t_handler"></param>
	void removeHandler(InputHandler* t_handler);

private:

	/// <summary>
	/// @brief A collection of handlers to broadcast our input to
	/// </summary>
	std::set<InputHandler*> m_handlers;

protected:

	/// <summary>
	/// @brief Broadcasts an input notification to all registered observers
	/// </summary>
	/// <param name="t_event">Type of input event</param>
	void notify(InputEvent t_event);
};

#endif // !INPUT_INTERFACE_H