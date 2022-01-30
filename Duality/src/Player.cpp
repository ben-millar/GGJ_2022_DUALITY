#include <Player.h>

Player::Player() :
	m_physicsBody({ 1860.f, 200.f }, 0.4f, 400.f, 0.7f)
{
	m_animations["idle"] = {
		{0,0,192,170}
	};

	m_animations["run"] = {
		{0,0,192,170},
		{192,0,192,170},
		{384,0,192,170},
		{576,0,192,170},
		{768,0,192,170}
	};

	m_animations["jump"] = {
		{0,0,192,170},
		{192,0,192,170},
		{384,0,192,170},
		{576,0,192,170},
		{768,0,192,170},
		{960,0,192,170},
		{1152,0,192,170},
		{1344,0,192,170},
		{1536,0,192,170},
		{1728,0,192,170},
		{1920,0,192,170},
		{2112,0,192,170},
		{2304,0,192,170}
	};

	m_sprite.setTexture(TextureManager::getInstance()->getTexture("idle"));
	m_sprite.setFrames(m_animations.at("idle"));
	m_sprite.loop(true);
	m_sprite.setFrameDelay(sf::seconds(0.1f));

	m_collider.setFillColor(sf::Color::Red);
	m_collider.setRadius(30.0f);
	m_collider.setOrigin(sf::Vector2f(30.0f, 30.0f));
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height / 2));
	//m_sprite.setPosition(m_collider.getPosition() + sf::Vector2f(30.0f, 30.0f));
	
}

////////////////////////////////////////////////////////////

void Player::update(sf::Time t_dT)
{
	m_physicsBody.update(t_dT);
	m_collider.setPosition(*m_physicsBody.getPosition());
	m_sprite.setPosition(*m_physicsBody.getPosition() - sf::Vector2f{40.f, 70.f});
	m_sprite.update();
	

	m_sprite.setPosition(m_collider.getPosition() - sf::Vector2f(0,33));


	auto v = *m_physicsBody.getVelocity();
	float relativeSpeed = int(fabsf(v.x) / 4.f) / 100.f; // Lose some precision :) I'm sorry for this

	if (!relativeSpeed && PlayerState::RUNNING == m_currentState)
		setState(PlayerState::IDLE);

	if (PlayerState::RUNNING == m_currentState)
		m_sprite.setAnimationSpeed(relativeSpeed);
}

////////////////////////////////////////////////////////////

void Player::moveLeft(sf::Time t_dT)
{
	if (PlayerState::IDLE == m_currentState)
		setState(PlayerState::RUNNING);

	m_physicsBody.addForce({ -1.f, 0.f }, t_dT);
	m_sprite.setScale(sf::Vector2f( - .7, .7));
}

////////////////////////////////////////////////////////////

void Player::moveRight(sf::Time t_dT)
{
	if (PlayerState::IDLE == m_currentState)
		setState(PlayerState::RUNNING);

	m_physicsBody.addForce({ 1.f, 0.f }, t_dT);
	m_sprite.setScale(sf::Vector2f(.7, .7));
}

////////////////////////////////////////////////////////////

void Player::setState(PlayerState t_state)
{
	m_currentState = t_state;

	switch (t_state)
	{
	case PlayerState::IDLE:
		cout << "Setting state: IDLE" << endl;
		m_sprite.setTexture(TextureManager::getInstance()->getTexture("idle"));
		m_sprite.setFrames(m_animations.at("idle"));
		break;
	case PlayerState::RUNNING:
		cout << "Setting state: RUNNING" << endl;
		m_sprite.setTexture(TextureManager::getInstance()->getTexture("jump"));
		m_sprite.setFrames(m_animations.at("jump"));
		m_sprite.loop(true);
		break;
	case PlayerState::JUMPING:
		cout << "Setting state: JUMPING" << endl;
		m_sprite.setTexture(TextureManager::getInstance()->getTexture("jump"));
		m_sprite.setFrames(m_animations.at("jump"));
		m_sprite.setFrameDelay(sf::seconds(0.05f));
		m_sprite.loop(false);
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////

void Player::jump()
{
	if (canJump && m_amountOfJumps > 0)
	{
		m_amountOfJumps--;

		sf::Vector2f force = { 0.f, m_jumpForce };
		m_physicsBody.addForce(force, sf::seconds(1.f), ForceMode::IMPULSE);
		canJump = false;

		setState(PlayerState::JUMPING);
	}
}

void Player::bounce()
{
	if (bounceTimer.getElapsedTime() > sf::seconds(.05f))
	{
		bounceTimer.restart();
		sf::Vector2f force = { 0.f, m_jumpForce * 3 };
		m_physicsBody.addForce(force, sf::seconds(1.f), ForceMode::IMPULSE);

		setState(PlayerState::JUMPING);
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
