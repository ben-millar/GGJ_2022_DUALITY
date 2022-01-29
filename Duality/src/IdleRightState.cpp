#include "IdleRightState.h"

PlayerState* IdleRightState::handleInput(InputEvent t_event)
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
        default:
            break;
        }
    }
    else
    {
        switch (t_event.ID)
        {
        case InputID::FALLING:
            return new FallingRightState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void IdleRightState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::RIGHT))
        p.setPlayerState(new WalkRightState());
}

///////////////////////////////////////////////////////////////

void IdleRightState::enter(Player& p)
{
    if (InputHandler::getInstance()->isPressed(InputID::JUMP))
        p.setPlayerState(new JumpingRightState());

    std::cout << "Entering IdleRightState" << std::endl;
}

///////////////////////////////////////////////////////////////

void IdleRightState::exit(Player& p)
{
    std::cout << "Exiting IdleRightState" << std::endl;
}
