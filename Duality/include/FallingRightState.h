#ifndef FALLING_RIGHT_STATE_H
#define FALLING_RIGHT_STATE_H

#include "PlayerState.h"

class FallingRightState :
	public PlayerState
{
public:
	FallingRightState() = default;
	virtual ~FallingRightState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "IdleRightState.h"

#endif