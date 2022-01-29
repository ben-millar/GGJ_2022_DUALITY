#ifndef PLAYER_H
#define PLAYER_H

#include "Globals.h"
#include "PhysicsBody.h"
#include "PlayerState.h"

class Player
{
public:
	Player(sf::Vector2f t_position);
	~Player() = default;

	void handleInput(InputEvent t_event);
	void update(sf::Time t_dT);

	void moveLeft(sf::Time t_dT);

	void moveRight(sf::Time t_dT);

	PhysicsBody& getPhysicsBody() { return m_physicsBody; }

	void jump();

	PlayerState* getPlayerState() { return m_state; }
	void setPlayerState(PlayerState* t_state);

	void draw(sf::RenderWindow& t_window);

private:
	InputHandler* p_inputHandler{ nullptr };
	PlayerState* m_state{ nullptr };
	PhysicsBody m_physicsBody;
	sf::CircleShape m_shape;

	float m_jumpForce = -600.f;
};

#endif