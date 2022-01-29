#ifndef JUMPING_LEFT_STATE_H
#define JUMPING_LEFT_STATE_H

#include "PlayerState.h"

class JumpingLeftState :
    public PlayerState
{
public:
	JumpingLeftState() = default;
	virtual ~JumpingLeftState() = default;
	virtual PlayerState* handleInput(InputEvent t_event) override;
	virtual void update(Player&, sf::Time t_dT) override;
	virtual void enter(Player&) override;
	virtual void exit(Player&) override;
};

#include "FallingLeftState.h"

#endif