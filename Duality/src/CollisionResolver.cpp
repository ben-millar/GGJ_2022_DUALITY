#include "..\include\CollisionResolver.h"

void CollisionResolver::resolvePlayerPlatform(Player* t_player, StaticPhysicsObject* t_platform)
{
	sf::Vector2f nearestPoint = t_player->getCenter();
	float halfWidth = t_platform->getBody()->getSize().x / 2;
	float halfHeight = t_platform->getBody()->getSize().y / 2;
	nearestPoint.x = std::clamp(nearestPoint.x, -halfWidth, halfWidth);
	nearestPoint.y = std::clamp(nearestPoint.y, -halfHeight, halfHeight);



	sf::Vector2f vectorBetween = nearestPoint - t_player->getCenter();
	MathUtils::normalise(vectorBetween);
	t_player->getCollider()->move(vectorBetween);
	t_player->getCollider()->setFillColor(sf::Color::Green);

}
