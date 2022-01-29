#include <Player.h>

Player::Player(sf::Vector2f t_position) :
	m_physicsBody(t_position, 0.4f, 400.f, 1.f)
{
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setRadius(20.0f);
	m_shape.setOrigin(sf::Vector2f(20.0f, 20.0f));
}

////////////////////////////////////////////////////////////

void Player::update(sf::Time t_dT)
{
	m_physicsBody.update(t_dT);
	m_shape.setPosition(*m_physicsBody.getPosition());
}

////////////////////////////////////////////////////////////

void Player::moveLeft(sf::Time t_dT)
{
	m_physicsBody.addForce({ -1.f, 0.f }, t_dT);
}

////////////////////////////////////////////////////////////

void Player::moveRight(sf::Time t_dT)
{
	m_physicsBody.addForce({ 1.f, 0.f }, t_dT);
}

////////////////////////////////////////////////////////////

void Player::jump()
{
	sf::Vector2f force = { 0.f, m_jumpForce };
	m_physicsBody.addForce(force, sf::seconds(1.f), ForceMode::IMPULSE);
}

////////////////////////////////////////////////////////////

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

////////////////////////////////////////////////////////////

sf::CircleShape* Player::getCollider()
{
	return &m_shape;
}