#ifndef PLAYER_H
#define PLAYER_H

#include <Globals.h>
#include <PhysicsBody.h>
#include <AnimatedSprite.h>
#include <TextureManager.h>

class Player
{
public:
	Player();
	~Player() = default;

	void update(sf::Time t_dT);

	void moveLeft(sf::Time t_dT);

	void moveRight(sf::Time t_dT);

	void jump();

	void bounce(); //method for bounce pad collisions

	void draw(sf::RenderWindow& t_window);

	sf::CircleShape* getCollider();

	PhysicsBody* getPhysicsBody() { return &m_physicsBody; }

	int getAmountJumps() { return m_amountOfJumps; };
	void setJumps(int t_jumps) { m_amountOfJumps = t_jumps; };
	void allowJump();

private:
	PhysicsBody m_physicsBody;
	sf::CircleShape m_collider;
	AnimatedSprite m_sprite;
	bool canJump = true;
	float m_jumpForce = -600.f;
	bool canBounce = true;
	int m_amountOfJumps = 5;
	sf::Clock bounceTimer;
};

#endif