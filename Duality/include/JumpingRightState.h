#ifndef JUMPING_RIGHT_STATE_H
#define JUMPING_RIGHT_STATE_H

#include "PlayerState.h"

class JumpingRightState :
    public PlayerState
{
public:
	JumpingRightState() = default;
	virtual ~JumpingRightState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "FallingRightState.h"

#endif