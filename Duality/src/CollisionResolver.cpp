#include "..\include\CollisionResolver.h"

void CollisionResolver::resolvePlayerPlatform(Player* t_player, StaticPhysicsObject* t_platform)
{
	sf::Vector2f nearestPoint = MathUtils::nearestPointOnRect(t_platform->getBody()->getGlobalBounds(), t_player->getCenter());

	sf::Vector2f lineOfCollision = t_player->getCenter() - nearestPoint;

	sf::Vector2f vectorBetween = nearestPoint - t_player->getCenter();
	MathUtils::normalise(vectorBetween);
	t_player->getCollider()->move(vectorBetween);
	t_player->getCollider()->setFillColor(sf::Color::Green);

}
