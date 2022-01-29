#include "StaticPhysicsObject.h"

StaticPhysicsObject::StaticPhysicsObject(sf::Vector2f bodySize, sf::Vector2f bodyPosition)
{
	body.setSize(bodySize);
	body.setPosition(bodyPosition);
	
	

}

sf::RectangleShape* StaticPhysicsObject::getBody()
{
	return &body;
}

sf::Vector2f StaticPhysicsObject::getCenter()
{
	return body.getPosition() + body.getSize() / 2.0f;
}
