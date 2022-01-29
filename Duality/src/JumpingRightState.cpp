#include "JumpingRightState.h"

PlayerState* JumpingRightState::handleInput(InputEvent t_event)
{
    if (InputType::PRESSED == t_event.type)
    {
        switch (t_event.ID)
        {
        case InputID::LEFT:
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
            return new FallingRightState();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////

void JumpingRightState::update(Player& p, sf::Time t_dT)
{
    if (InputHandler::getInstance()->isPressed(InputID::RIGHT))
        p.moveRight(t_dT);

    if (p.getPhysicsBody().getVelocity()->y > 0.f)
        p.setPlayerState(new FallingRightState());
}

///////////////////////////////////////////////////////////////

void JumpingRightState::enter(Player& p)
{
    p.jump();
    std::cout << "Entering JumpingRightState" << std::endl;
}

///////////////////////////////////////////////////////////////

void JumpingRightState::exit(Player& p)
{
    std::cout << "Exiting JumpingRightState" << std::endl;
}
