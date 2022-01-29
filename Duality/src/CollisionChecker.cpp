#include "CollisionChecker.h"

bool CollisionChecker::circleToAABB(sf::RectangleShape* rect, sf::CircleShape* circle)
{
    sf::Vector2f circlePos = circle->getPosition();

    sf::Vector2f nearestPoint = MathUtils::nearestPointOnRect(
        rect->getGlobalBounds(),
        circlePos
    );

    return (MathUtils::squaredLength(circlePos - nearestPoint) < powf(circle->getRadius(), 2));
}
