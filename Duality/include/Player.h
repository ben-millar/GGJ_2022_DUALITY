#ifndef PLAYER_H
#define PLAYER_H

#include <Globals.h>
#include <PhysicsBody.h>

class Player
{
public:
	Player(sf::Vector2f t_position);
	~Player() = default;

	void update(sf::Time t_dT);

	void moveLeft(sf::Time t_dT);

	void moveRight(sf::Time t_dT);

	void jump();

	void draw(sf::RenderWindow& t_window);

	sf::CircleShape* getCollider();

	PhysicsBody* getPhysicsBody() { return &m_physicsBody; }
	void allowJump();

private:
	PhysicsBody m_physicsBody;
	sf::CircleShape m_shape;
	bool canJump = true;
	float m_jumpForce = -600.f;
};

#endif