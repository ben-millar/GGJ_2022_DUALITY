#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Globals.h>
#include <Player.h>
#include "StaticPhysicsObject.h"
#include "CollisionChecker.h"

#include "CollisionResolver.h"

#include "TextureManager.h"
#include "UI.h"


using namespace std;

class Game
{
private:
	array<vector<StaticPhysicsObject*>, 11> m_platforms;
	vector<StaticPhysicsObject*>* p_currentPlatforms;

	array <vector<StaticPhysicsObject*>, 11> m_hazards;
	vector<StaticPhysicsObject*>* p_currentHazards;


	int m_jumpsPerLevel[11];
	array <vector<StaticPhysicsObject*>, 11> m_bouncePads;
	vector<StaticPhysicsObject*>* p_currentBouncePads;

	array<const char*, 11> m_textureIDs;

	array<sf::Vector2f, 2> m_playerStartPositions{
		{
			{1880.f, 750.f},
			{100.f, 870.f}
		}
	};

	/// <summary>
	/// Creates an sf::RenderWindow on the stack
	/// </summary>
	/// <param name="t_title">Title for the sf::RenderWindow</param>
	/// <returns>A pointer to a stack-allocated sf::RenderWindow</returns>
	sf::RenderWindow* createWindow(std::string t_title);
	sf::RenderWindow* m_window{ nullptr };

	sf::Music m_backgroundMusic;
	sf::Sound m_deathSound;
	sf::SoundBuffer m_deathSoundBuffer;

	sf::Sprite m_background;
	sf::RectangleShape m_magicTransitionRectangle;

	bool m_transitioning{ false };
	UI playerUI;
	Player* m_player;
	int m_currentLevel{ 0 };
	

public:
	Game() = default;
	~Game() = default;

	/// <summary>
	/// Initializes and starts the game loop
	/// </summary>
	void run();

	void loadLevel(int t_level);

	void setupPlatforms();

	void loadTextures();

	void loadAudio();

	/// <summary>
	/// Handles system events (input, etc.)
	/// </summary>
	void processEvents();

	sf::View view;

	void populateJumpAmounts();
	void checkIfPlayerCanJump();

	/// <summary>
	/// Called once every game tick
	/// </summary>
	/// <param name="t_dTime">Time in seconds since the last update</param>
	void update(sf::Time t_dTime);

	/// <summary>
	/// Play a transition effect between screens
	/// </summary>
	void transition();

	/// <summary>
	/// Clears, redraws and displays the framebuffer
	/// </summary>
	void render();
};

#endif