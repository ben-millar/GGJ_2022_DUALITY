#include <Game.h>

void Game::run()
{
	m_window = createWindow("GGJ 2022 | Duality");
	m_window->setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	// INITIALISE STUFF HERE
	m_player = new Player({ 400.f, 400.f });



	StaticPhysicsObject* platform = new StaticPhysicsObject(sf::Vector2f(200,50), sf::Vector2f(300,1550));
	StaticPhysicsObject* platform2 = new StaticPhysicsObject(sf::Vector2f(200, 50), sf::Vector2f(600, 1200));


	platforms.push_back(platform);
	platforms.push_back(platform2);

	StaticPhysicsObject* spike = new StaticPhysicsObject(sf::Vector2f(50, 50), sf::Vector2f(750, 1550));
	spike->getBody()->setFillColor(sf::Color::Red);
	
	StaticPhysicsObject* bouncepad = new StaticPhysicsObject(sf::Vector2f(50, 50), sf::Vector2f(950, 1600));
	bouncepad->getBody()->setFillColor(sf::Color::Green);
	bouncepads.push_back(bouncepad);


	hazards.push_back(spike);


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

	m_player->draw(*m_window);

	for (auto platform : platforms)
	{
		m_window->draw(*platform->getBody());
	}

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
