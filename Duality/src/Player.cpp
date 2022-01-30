#include <Player.h>

Player::Player() :
	m_physicsBody({ 1860.f, 200.f }, 0.4f, 400.f, 0.7f)
{
	m_sprite.setTexture(TextureManager::getInstance()->getTexture("player"));
	m_sprite.setFrames({
		{0,0,137,170},
		{137,0,137,170},
		{274,0,137,170},
		{411,0,137,170},
		{548,0,137,170}
	});
	m_sprite.loop(true);
	m_sprite.setFrameDelay(sf::seconds(0.1f));

	m_collider.setFillColor(sf::Color::Red);
	m_collider.setRadius(30.0f);
	m_collider.setOrigin(sf::Vector2f(30.0f, 30.0f));
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(m_collider.getPosition() + sf::Vector2f(30.0f, 30.0f));
	
}

////////////////////////////////////////////////////////////

void Player::update(sf::Time t_dT)
{
	m_physicsBody.update(t_dT);
	m_collider.setPosition(*m_physicsBody.getPosition());
	m_sprite.setPosition(*m_physicsBody.getPosition() - sf::Vector2f{40.f, 70.f});
	m_sprite.update();
	

	m_sprite.setPosition(m_collider.getPosition() - sf::Vector2f(0,50));


	auto v = *m_physicsBody.getVelocity();
	float relativeSpeed = int(fabsf(v.x) / 4.f) / 100.f; // Lose some precision :) I'm sorry for this

	m_sprite.setAnimationSpeed(relativeSpeed);


}

////////////////////////////////////////////////////////////

void Player::moveLeft(sf::Time t_dT)
{
	m_physicsBody.addForce({ -1.f, 0.f }, t_dT);
	m_sprite.setScale(sf::Vector2f( - .7, .7));
}

////////////////////////////////////////////////////////////

void Player::moveRight(sf::Time t_dT)
{
	m_physicsBody.addForce({ 1.f, 0.f }, t_dT);
	m_sprite.setScale(sf::Vector2f(.7, .7));
}

////////////////////////////////////////////////////////////

void Player::jump()
{
	if (canJump)
	{
		sf::Vector2f force = { 0.f, m_jumpForce };
		m_physicsBody.addForce(force, sf::seconds(1.f), ForceMode::IMPULSE);
		canJump = false;
	}
}

void Player::bounce()
{
	
	if (bounceTimer.getElapsedTime() > sf::seconds(.05f))
	{
		bounceTimer.restart();
		sf::Vector2f force = { 0.f, m_jumpForce * 3 };
		m_physicsBody.addForce(force, sf::seconds(1.f), ForceMode::IMPULSE);
	}
}

////////////////////////////////////////////////////////////

void Player::draw(sf::RenderWindow& t_window)
{
	m_sprite.draw(t_window);
	//t_window.draw(m_collider);
}

////////////////////////////////////////////////////////////

sf::CircleShape* Player::getCollider()
{
	return &m_collider;
}

////////////////////////////////////////////////////////////

void Player::allowJump()
{
	canJump = true;
}
