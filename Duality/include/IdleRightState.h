#ifndef IDLE_RIGHT_STATE_H
#define IDLE_RIGHT_STATE_H

#include "PlayerState.h"

class IdleRightState :
    public PlayerState
{
public:
	IdleRightState() = default;
	virtual ~IdleRightState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "WalkRightState.h"
#include "WalkLeftState.h"
#include "JumpingRightState.h"

#endif