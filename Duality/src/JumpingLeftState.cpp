#include "JumpingLeftState.h"

PlayerState* JumpingLeftState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::RIGHT:
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
            return new FallingLeftState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void JumpingLeftState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::LEFT))
        p.moveLeft(t_dT);

    if (p.getPhysicsBody().getVelocity()->y > 0.f)
        p.setPlayerState(new FallingLeftState());
}

///////////////////////////////////////////////////////////////

void JumpingLeftState::enter(Player& p)
{
    p.jump();
    std::cout << "Entering JumpingLeftState" << std::endl;
}

///////////////////////////////////////////////////////////////

void JumpingLeftState::exit(Player& p)
{
    std::cout << "Exiting JumpingLeftState" << std::endl;
}
