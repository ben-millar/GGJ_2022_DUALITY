#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <Player.h>
#include "StaticPhysicsObject.h"
#include "CollisionChecker.h"
#include <algorithm>
#include "CollisionResolver.h"

#include "TextureManager.h"

using namespace std;

class Game
{
public:
	Game() = default;
	~Game() = default;

	/// <summary>
	/// Initializes and starts the game loop
	/// </summary>
	void run();

	void setupPlatforms();

	void loadTextures();

	void setupSprites();

	/// <summary>
	/// Handles system events (input, etc.)
	/// </summary>
	void processEvents();

	/// <summary>
	/// Called once every game tick
	/// </summary>
	/// <param name="t_dTime">Time in seconds since the last update</param>
	void update(sf::Time t_dTime);

	/// <summary>
	/// Clears, redraws and displays the framebuffer
	/// </summary>
	void render();
	
private:
	std::vector<StaticPhysicsObject*> platforms;
	std::vector<StaticPhysicsObject*> hazards;
	std::vector<StaticPhysicsObject*> bouncepads;

	/// <summary>
	/// Creates an sf::RenderWindow on the stack
	/// </summary>
	/// <param name="t_title">Title for the sf::RenderWindow</param>
	/// <returns>A pointer to a stack-allocated sf::RenderWindow</returns>
	sf::RenderWindow* createWindow(std::string t_title);
	sf::RenderWindow* m_window{ nullptr };

	sf::Sprite m_background;

	Player* m_player;
};

#endif