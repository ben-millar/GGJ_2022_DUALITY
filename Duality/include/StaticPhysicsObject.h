#pragma once
#include "Globals.h"
#include "MathUtils.h"

class StaticPhysicsObject
{
public:
	StaticPhysicsObject(sf::Vector2f bodySize, sf::Vector2f bodyPosition);
	sf::RectangleShape* getBody();
	sf::Vector2f getCenter();
private:
	sf::RectangleShape body;
	sf::Texture bodyTexture;


};

