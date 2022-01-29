#include "WalkLeftState.h"

PlayerState* WalkLeftState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::RIGHT:
            return new WalkRightState();
            break;
        case InputID::JUMP:
            return new JumpingLeftState();
            break;
        default:
            break;
        }
    }
    else if (InputType::RELEASED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::LEFT:
            return new IdleLeftState();
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

void WalkLeftState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::LEFT))
        p.moveLeft(t_dT);
}

///////////////////////////////////////////////////////////////

void WalkLeftState::enter(Player& p)
{
    std::cout << "Entering WalkLeftState" << std::endl;
}

///////////////////////////////////////////////////////////////

void WalkLeftState::exit(Player& p)
{
    std::cout << "Exiting WalkLeftState" << std::endl;
}
