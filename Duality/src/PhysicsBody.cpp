#include <PhysicsBody.h>

PhysicsBody::PhysicsBody(sf::Vector2f t_position, float t_timeToMaxSpeed, float t_maxSpeed, float t_timeToFullStop) :
	m_position{ t_position },
	TIME_TO_MAX_SPEED{ sf::seconds(t_timeToMaxSpeed) },
	MAX_SPEED{ t_maxSpeed },
	TIME_TO_FULL_STOP{ sf::seconds(t_timeToFullStop) } {}

////////////////////////////////////////////////////////////

void PhysicsBody::update(sf::Time t_dT)
{
	m_position += m_velocity * t_dT.asSeconds();

	addForce(GRAVITY, t_dT, ForceMode::IMPULSE);

	decelerate(t_dT);
}


////////////////////////////////////////////////////////////

void PhysicsBody::addForce(sf::Vector2f t_force, sf::Time t_dT, ForceMode t_forceMode)
{
	switch (t_forceMode)
	{
	case ForceMode::IMPULSE:
		m_velocity += t_force * t_dT.asSeconds();
		break;
	case ForceMode::ACCELERATION:
		m_velocity += MathUtils::unit(t_force) * (MAX_SPEED / TIME_TO_MAX_SPEED.asSeconds()) * t_dT.asSeconds() * 2.0f;
		break;
	default:
		break;
	}

	throttleSpeed();
}

////////////////////////////////////////////////////////////

void PhysicsBody::throttleSpeed()
{
	if (fabsf(m_velocity.x) > MAX_SPEED)
		m_velocity.x = (m_velocity.x / fabsf(m_velocity.x)) * MAX_SPEED;
}

////////////////////////////////////////////////////////////

void PhysicsBody::decelerate(sf::Time t_dT)
{
	static const float MIN_VELOCITY = 1.0f;

	if (fabsf(m_velocity.x) > MIN_VELOCITY)
		// Decelerate by the sign of our velocity * deceleration * delta time
		m_velocity.x -= (m_velocity.x / fabsf(m_velocity.x)) * (MAX_SPEED / TIME_TO_FULL_STOP.asSeconds()) * t_dT.asSeconds();
}