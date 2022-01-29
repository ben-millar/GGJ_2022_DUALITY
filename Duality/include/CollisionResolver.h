
#include <SFML/Graphics.hpp>
#include "MathUtils.h"
#include "Player.h"
#include "StaticPhysicsObject.h"

static class CollisionResolver
{
public:
	static void resolvePlayerPlatform(Player* t_player, StaticPhysicsObject* t_platform);


private:

};