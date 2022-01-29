#include <Game.h>

void Game::run()
{
	m_window = createWindow("GGJ 2022 | Duality");
	m_window->setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	p_inputHandler = InputHandler::getInstance();
	m_keyboard.addHandler(p_inputHandler);

	m_player = new Player({ 400.f, 400.f });
	m_player->setPlayerState(new IdleRightState());

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
	sf::Event window_event;
	while (m_window->pollEvent(window_event))
	{
		// HANDLE EVENTS HERE

		if (window_event.type == sf::Event::Closed)
			m_window->close();

		m_keyboard.handleInput(window_event);

		InputEvent e;
		p_inputHandler->poll(e);

		if (InputID::EXIT == e.ID)
			m_window->close();
		
		m_player->handleInput(e);
	}
}

////////////////////////////////////////////////////////////

void Game::update(sf::Time t_dTime)
{
	m_player->update(t_dTime);
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
