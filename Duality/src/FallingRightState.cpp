#include "FallingRightState.h"

PlayerState* FallingRightState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::LEFT:
            return new FallingLeftState();
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
            return new IdleRightState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void FallingRightState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::RIGHT))
        p.moveRight(t_dT);
}

///////////////////////////////////////////////////////////////

void FallingRightState::enter(Player& p)
{
    std::cout << "Entering FallingRightState" << std::endl;
}

///////////////////////////////////////////////////////////////

void FallingRightState::exit(Player& p)
{
    std::cout << "Exiting FallingRightState" << std::endl;
}
