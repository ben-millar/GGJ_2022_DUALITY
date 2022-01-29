#include "InputInterface.h"

void InputInterface::addHandler(InputHandler* t_handler)
{
	m_handlers.insert(t_handler);
}

///////////////////////////////////////////////////////////////


void InputInterface::removeHandler(InputHandler* t_handler)
{
	m_handlers.erase(t_handler);
}

///////////////////////////////////////////////////////////////

void InputInterface::notify(InputEvent t_event)
{
	for (auto& it : m_handlers)
		it->onNotify(t_event);
}