#include "WalkRightState.h"

PlayerState* WalkRightState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::LEFT:
            return new WalkLeftState();
            break;
        case InputID::JUMP:
            return new JumpingRightState();
            break;
        default:
            break;
        }
    }
    else if (InputType::RELEASED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::RIGHT:
            return new IdleRightState();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (t_event.ID)
        {
        case InputID::FALLING:
            return new FallingLeftState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void WalkRightState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::RIGHT))
        p.moveRight(t_dT);
}

///////////////////////////////////////////////////////////////

void WalkRightState::enter(Player& p)
{
    std::cout << "Entering WalkRightState" << std::endl;
}

///////////////////////////////////////////////////////////////

void WalkRightState::exit(Player& p)
{
    std::cout << "Exiting WalkRightState" << std::endl;
}
