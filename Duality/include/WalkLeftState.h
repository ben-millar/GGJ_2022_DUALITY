#ifndef WALK_LEFT_STATE_H
#define WALK_LEFT_STATE_H

#include "PlayerState.h"

class WalkLeftState :
    public PlayerState
{
public:
	WalkLeftState() = default;
	virtual ~WalkLeftState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "IdleLeftState.h"
#include "JumpingLeftState.h"

#endif