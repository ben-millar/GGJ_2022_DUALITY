#include "CollisionChecker.h"

bool CollisionChecker::circleToAABB(sf::RectangleShape* rect, sf::CircleShape* circle)
{
    float testX = circle->getPosition().x;
    float testY = circle->getPosition().y;

    // which edge is closest?
    if (circle->getPosition().x < rect->getPosition().x)
    {
        testX = rect->getPosition().x;      // test left edge
    }
    else if (circle->getPosition().x > rect->getPosition().x + rect->getSize().x)
    {
        testX = rect->getPosition().x + rect->getSize().x;   // right edge
    }

    if (circle->getPosition().y < rect->getPosition().y)
    {
        testY = rect->getPosition().y;      // top edge
    }

    else if (circle->getPosition().y > rect->getPosition().y + rect->getSize().y)
    {
        testY = rect->getPosition().y + rect->getSize().y;   // bottom edge
      
    }


    // get distance from closest edges
    float distX = circle->getPosition().x - testX;
    float distY = circle->getPosition().y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= circle->getRadius()) {
        return true;
    }
    return false;


    return false;
}
