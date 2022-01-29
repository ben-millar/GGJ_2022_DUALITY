#include "FallingLeftState.h"

PlayerState* FallingLeftState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::RIGHT:
            return new FallingRightState();
            break;
        default:
            break;
        }
    }
    else if (InputType::RELEASED == t_event.type)
    {
        switch (t_event.ID)
        {
        default:
            break;
        }
    }
    else
    {
        switch (t_event.ID)
        {
        case InputID::HIT_GROUND:
            return new IdleLeftState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void FallingLeftState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::LEFT))
        p.moveLeft(t_dT);
}

///////////////////////////////////////////////////////////////

void FallingLeftState::enter(Player& p)
{
    std::cout << "Entering FallingLeftState" << std::endl;
}

///////////////////////////////////////////////////////////////

void FallingLeftState::exit(Player& p)
{
    std::cout << "Exiting FallingLeftState" << std::endl;
}
