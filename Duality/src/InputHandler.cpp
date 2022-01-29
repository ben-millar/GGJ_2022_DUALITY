#include "InputHandler.h"

std::queue<InputEvent> InputHandler::m_inputQueue;
std::set<InputID> InputHandler::m_activeInputs;

void InputHandler::onNotify(InputEvent t_event)
{
	// Add this event to our queue
	m_inputQueue.push(t_event);

	// Update the active inputs
	if (InputType::PRESSED == t_event.type)
		m_activeInputs.insert(t_event.ID);
	else if (InputType::RELEASED == t_event.type)
		m_activeInputs.erase(t_event.ID);
}

///////////////////////////////////////////////////////////////

void InputHandler::poll(InputEvent& t_event)
{
	if (!m_inputQueue.empty())
	{
		t_event = m_inputQueue.front();
		m_inputQueue.pop();
	}
}

///////////////////////////////////////////////////////////////

bool InputHandler::isPressed(InputID t_ID)
{
	return static_cast<bool>(m_activeInputs.count(t_ID));
}