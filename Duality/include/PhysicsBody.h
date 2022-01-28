#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include <Globals.h>
#include <MathUtils.h>

enum class ForceMode
{
	ACCELERATION,	// This is taken as a unit vector throttled by our time to max speed
	IMPULSE			// This force is applied directly
};

class PhysicsBody
{
public:

	PhysicsBody(sf::Vector2f t_position, float t_timeToMaxSpeed, float t_maxSpeed, float t_timeToFullStop);
	~PhysicsBody() = default;

	/// <summary>
	/// Update our physics body along with the update loop
	/// </summary>
	/// <param name="t_dT">Time in seconds since last game update</param>
	void update(sf::Time t_dT);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_movementVector"></param>
	/// <param name="t_dT"></param>
	/// <param name="t_forceMode"></param>
	void addForce(sf::Vector2f t_movementVector, sf::Time t_dT, ForceMode t_forceMode = ForceMode::ACCELERATION);

	/// <summary>
	/// Get the current position of the physics body
	/// </summary>
	/// <returns>A non-const pointer to our const qualified position</returns>
	sf::Vector2f const* getPosition() { return &m_position; }

	/// <summary>
	/// Set the position of the physics body
	/// </summary>
	/// <param name="t_pos">An SF::Vector2f position to move our body to</param>
	void setPosition(sf::Vector2f t_pos) { m_position = t_pos; }

	/// <summary>
	/// Get the current velocity of the physics body
	/// </summary>
	/// <returns>A non-const pointer to our const qualified velocity</returns>
	sf::Vector2f const* getVelocity() { return &m_velocity; }

private:

	void throttleSpeed();

	/// <summary>
	/// Decelerate along our movement vector given our timeToFullStop
	/// </summary>
	/// <param name="t_dT">Time in seconds since last game update</param>
	void decelerate(sf::Time t_dT);

	const sf::Time TIME_TO_MAX_SPEED;
	const sf::Time TIME_TO_FULL_STOP;
	const float MAX_SPEED;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};

#endif