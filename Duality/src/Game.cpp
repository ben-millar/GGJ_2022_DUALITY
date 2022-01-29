#include <Game.h>

void Game::run()
{
	m_window = createWindow("GGJ 2022 | Duality");
	m_window->setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	// INITIALISE STUFF HERE
	m_player = new Player({ 125.f, 800.f });

	StaticPhysicsObject* spike = new StaticPhysicsObject(sf::Vector2f(50, 50), sf::Vector2f(750, 1550));
	spike->getBody()->setFillColor(sf::Color::Red);
	
	StaticPhysicsObject* bouncepad = new StaticPhysicsObject(sf::Vector2f(50, 50), sf::Vector2f(950, 1600));
	bouncepad->getBody()->setFillColor(sf::Color::Green);
	bouncepads.push_back(bouncepad);


	hazards.push_back(spike);

	setupPlatforms();
	loadTextures();
	setupSprites();

	while (m_window->isOpen())
	{
		sf::Time dT = clock.restart();
		lag += dT;

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		update(dT);
		render();
	}
}

////////////////////////////////////////////////////////////

void Game::setupPlatforms()
{
	// LEVEL 1 DAY
	platforms = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(300.f, 85.f), sf::Vector2f(0.f, 940.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 775.f), sf::Vector2f(0.f, 1025.f)),
		new StaticPhysicsObject(sf::Vector2f(250.f, 135.f), sf::Vector2f(450.f, 933.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 114.f), sf::Vector2f(664.f, 668.f)),
		new StaticPhysicsObject(sf::Vector2f(150.f, 144.f), sf::Vector2f(853.f, 935.f)),
		new StaticPhysicsObject(sf::Vector2f(158.f, 138.f), sf::Vector2f(1215.f, 1084.f)),
		new StaticPhysicsObject(sf::Vector2f(302.f, 90.f), sf::Vector2f(1425.f, 1216.f)),
		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 155.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};
}

////////////////////////////////////////////////////////////

void Game::loadTextures()
{
	auto tm = TextureManager::getInstance();
	tm->loadTexture("level1_day", "assets/images/level1Day.png");
	tm->loadTexture("level1_night", "assets/images/level1Night.png");
	tm->loadTexture("level2_day", "assets/images/level2DAY.png");
	tm->loadTexture("level2_night", "assets/images/level2NIGHT.png");
	tm->loadTexture("level3_day", "assets/images/level3DAY.png");
	tm->loadTexture("level3_night", "assets/images/level3NIGHT.png");
	tm->loadTexture("level4_day", "assets/images/level4DAY.png");
	tm->loadTexture("level4_night", "assets/images/level4NIGHT.png");
	tm->loadTexture("level5_day", "assets/images/level5DAY.png");
	tm->loadTexture("level6_night", "assets/images/level5NIGHT_END.png");
}

////////////////////////////////////////////////////////////

void Game::setupSprites()
{
	m_background.setTexture(*TextureManager::getInstance()->getTexture("level1_day"));
}

////////////////////////////////////////////////////////////

void Game::processEvents()
{
	sf::Event e;
	while (m_window->pollEvent(e))
	{
		// HANDLE EVENTS HERE

		if (e.type == sf::Event::Closed)
			m_window->close();

		if (e.type == sf::Event::KeyPressed)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_window->close();
				break;
			case sf::Keyboard::W:
				m_player->jump();
				break;
			case sf::Keyboard::Up:
				
				m_player->jump();
				break;
			default:
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////

void Game::update(sf::Time t_dTime)
{
	m_player->update(t_dTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_player->moveLeft(t_dTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_player->moveRight(t_dTime);



	for (auto platform : platforms)
	{
		if (CollisionChecker::circleToAABB(platform->getBody(), m_player->getCollider()))
		{
			m_player->allowJump();
			
			CollisionResolver::resolvePlayerPlatform(m_player, platform);
		}
	}

	for (auto hazard : hazards)
	{
		if (CollisionChecker::circleToAABB(hazard->getBody(), m_player->getCollider()))
		{
			std::cout << "player died" << std::endl;
		}
	}

	for (auto bouncepad : bouncepads)
	{
		if (CollisionChecker::circleToAABB(bouncepad->getBody(), m_player->getCollider()))
		{
			m_player->bounce();
		}
	}
}

////////////////////////////////////////////////////////////

void Game::render()
{
	m_window->clear(sf::Color::Black);

	m_window->draw(m_background);

	m_player->draw(*m_window);


	for (auto hazard : hazards)
	{
		m_window->draw(*hazard->getBody());
	}


	for (auto bouncepad : bouncepads)
	{
		m_window->draw(*bouncepad->getBody());
	}
	m_window->display();
}


///////////////////////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title, sf::Style::Titlebar | sf::Style::Close);
}
