#include "..\include\CollisionResolver.h"

void CollisionResolver::resolvePlayerPlatform(Player* t_player, StaticPhysicsObject* t_platform)
{
	auto pb = t_player->getPhysicsBody();
	auto platformBounds = t_platform->getBody()->getGlobalBounds();
	sf::Vector2f nearestPoint = MathUtils::nearestPointOnRect(platformBounds, *pb->getPosition());

	sf::Vector2f lineOfCollision = *pb->getPosition() - nearestPoint;
	pb->setPosition(nearestPoint + MathUtils::unit(lineOfCollision) * 30.f);

	if (pb->getPosition()->y > platformBounds.top &&
		pb->getPosition()->y < (platformBounds.top + platformBounds.height))
		return;

	auto v = *pb->getVelocity();
	pb->setVelocity({ v.x, 0.f });
}
