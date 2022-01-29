#ifndef FALLING_LEFT_STATE_H
#define FALLING_LEFT_STATE_H

#include "PlayerState.h"

class FallingLeftState :
	public PlayerState
{
public:
	FallingLeftState() = default;
	virtual ~FallingLeftState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "IdleLeftState.h"

#endif