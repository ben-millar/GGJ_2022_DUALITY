#include "..\include\CollisionResolver.h"

void CollisionResolver::resolvePlayerPlatform(Player* t_player, StaticPhysicsObject* t_platform)
{
	auto pb = t_player->getPhysicsBody();
	sf::Vector2f nearestPoint = MathUtils::nearestPointOnRect(t_platform->getBody()->getGlobalBounds(), *pb->getPosition());

	sf::Vector2f lineOfCollision = *pb->getPosition() - nearestPoint;
	pb->setPosition(nearestPoint + MathUtils::unit(lineOfCollision) * 20.f);

	auto v = *pb->getVelocity();
	pb->setVelocity({ v.x, 0.f });
}
