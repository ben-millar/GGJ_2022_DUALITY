#ifndef IDLE_LEFT_STATE_H
#define IDLE_LEFT_STATE_H

#include "PlayerState.h"

class IdleLeftState :
    public PlayerState
{
public:
	IdleLeftState() = default;
	virtual ~IdleLeftState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "WalkLeftState.h"
#include "WalkRightState.h"
#include "JumpingLeftState.h"

#endif