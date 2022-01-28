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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_player->moveLeft(t_dTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_player->moveRight(t_dTime);
}

////////////////////////////////////////////////////////////

void Game::render()
{
	m_window->clear(sf::Color::Black);

	m_player->draw(*m_window);

	m_window->display();
}


///////////////////////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title, sf::Style::Titlebar | sf::Style::Close);
}
