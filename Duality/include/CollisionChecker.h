#pragma once
#include "Globals.h"
#include "SFML/Graphics.hpp"
#include <iostream>

static class CollisionChecker
{
public:
	static bool circleToAABB(sf::RectangleShape* rect, sf::CircleShape* circle);

};

