#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <queue>
#include <set>

#include "InputEvent.h"

class InputHandler
{
public:
	static InputHandler* getInstance()
	{
		static InputHandler instance;
		return &instance;
	}

	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;

	/// <summary>
	/// @brief Upon recieving a new event, add it to our queue
	/// </summary>
	/// <param name="t_event">Event to add</param>
	static void onNotify(InputEvent t_event);
	
	/// <summary>
	/// @brief Returns the first input event in the queue
	/// </summary>
	/// <param name="t_event">Reference to input event to copy ToS event to</param>
	static void poll(InputEvent& t_event);

	/// <summary>
	/// @brief Check if a given input is currently pressed
	/// </summary>
	/// <param name="t_ID">ID of input to check</param>
	/// <returns>True if currently pressed, otherwise false</returns>
	static bool isPressed(InputID t_ID);

private:
	InputHandler() {}
	static std::queue<InputEvent> m_inputQueue;
	static std::set<InputID> m_activeInputs;
};

#endif // !INPUT_HANDLER_H