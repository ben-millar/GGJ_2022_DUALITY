#include "IdleLeftState.h"

PlayerState* IdleLeftState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::LEFT:
            return new WalkLeftState();
            break;
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

void IdleLeftState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::LEFT))
        p.setPlayerState(new WalkLeftState());
}

///////////////////////////////////////////////////////////////

void IdleLeftState::enter(Player& p)
{
    if (InputHandler::getInstance()->isPressed(InputID::JUMP))
        p.setPlayerState(new JumpingLeftState());

    std::cout << "Entering IdleLeftState" << std::endl;
}

///////////////////////////////////////////////////////////////

void IdleLeftState::exit(Player& p)
{
    std::cout << "Exiting IdleLeftState" << std::endl;
}
