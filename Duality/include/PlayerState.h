#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "InputHandler.h"

class Player;

class PlayerState {
public:
	virtual ~PlayerState() {};
	virtual PlayerState* handleInput(InputEvent t_event) = 0;
	virtual void update(Player&, sf::Time t_dT) = 0;
	virtual void enter(Player&) = 0;
	virtual void exit(Player&) = 0;
protected:
};

#include "Player.h"

#endif