#include <Game.h>

void Game::run()
{
	m_window = createWindow("GGJ 2022 | Duality");
	m_window->setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	loadTextures();
	loadAudio();
	setupPlatforms();

	m_player = new Player();

	m_magicTransitionRectangle.setFillColor(sf::Color::Transparent);
	m_magicTransitionRectangle.setSize({ float(WINDOW_WIDTH), float(WINDOW_HEIGHT) });

	loadLevel(m_currentLevel);
	m_backgroundMusic.play();
	m_backgroundMusic.setLoop(true);

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

void Game::loadLevel(int t_level)
{
	auto tm = TextureManager::getInstance();
	m_background.setTexture(*tm->getTexture(m_textureIDs.at(t_level)));
	p_currentPlatforms = &m_platforms.at(t_level);
	p_currentHazards = &m_hazards.at(t_level);
	p_currentBouncePads = &m_bouncePads.at(t_level);
	m_player->getPhysicsBody()->setPosition(m_playerStartPositions[t_level % 2]);
	m_player->getPhysicsBody()->setVelocity({ 0.f,0.f });
	m_currentLevel = t_level;
	m_transitioning = true;
}

////////////////////////////////////////////////////////////

void Game::setupPlatforms()
{
	// LEVEL 1 DAY
	m_platforms[0] = {
		//new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
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

	// LEVEL 1 NIGHT
	m_platforms[1] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 845.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(193.f, 230.f), sf::Vector2f(235.f, 1570.f)),
		new StaticPhysicsObject(sf::Vector2f(205.f, 670.f), sf::Vector2f(428.f, 1130.f)),
		new StaticPhysicsObject(sf::Vector2f(170.f, 547.f), sf::Vector2f(633.f, 1253.f)),
		new StaticPhysicsObject(sf::Vector2f(220.f, 408.f), sf::Vector2f(803.f, 1392.f)),
		new StaticPhysicsObject(sf::Vector2f(208.f, 547.f), sf::Vector2f(1022.f, 1253.f)),
		new StaticPhysicsObject(sf::Vector2f(335.f, 117.f), sf::Vector2f(1320.f, 1020.f)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(1600.f, 193.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(988.f, 320.f), sf::Vector2f(612.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(343.f, 554.f), sf::Vector2f(612.f, 0.f)),
		//new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};

	// LEVEL 2 DAY
	m_platforms[2] = {
		//new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 865.f), sf::Vector2f(0.f, 940.f)),
		new StaticPhysicsObject(sf::Vector2f(153.f, 147.f), sf::Vector2f(350.f, 800.f)),
		new StaticPhysicsObject(sf::Vector2f(142.f, 130.f), sf::Vector2f(557.f, 441.f)),
		new StaticPhysicsObject(sf::Vector2f(154.f, 165.f), sf::Vector2f(641.f, 931.f)),
		new StaticPhysicsObject(sf::Vector2f(891.f, 143.f), sf::Vector2f(1109.f, 874.f)),
		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f))
	};

	m_hazards[2] = {
		new StaticPhysicsObject(sf::Vector2f(57, 25), sf::Vector2f(1210, 845)),
		new StaticPhysicsObject(sf::Vector2f(293, 25), sf::Vector2f(1400, 845))
	};

	// LEVEL 2 NIGHT
	m_platforms[3] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 845.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(119, 122), sf::Vector2f(380, 1270)),
		new StaticPhysicsObject(sf::Vector2f(119, 122), sf::Vector2f(762, 1270)),
		new StaticPhysicsObject(sf::Vector2f(137, 122), sf::Vector2f(1077, 1122)),
		new StaticPhysicsObject(sf::Vector2f(260, 37), sf::Vector2f(1212, 1210)),
		new StaticPhysicsObject(sf::Vector2f(130, 124), sf::Vector2f(1474, 1048)),
		new StaticPhysicsObject(sf::Vector2f(177, 118), sf::Vector2f(1675, 938)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(1600.f, 193.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(988.f, 320.f), sf::Vector2f(612.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(343.f, 554.f), sf::Vector2f(612.f, 0.f)),
		//new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};

	m_hazards[3] = {
		new StaticPhysicsObject(sf::Vector2f(300, 55), sf::Vector2f(495, 1630)),
		new StaticPhysicsObject(sf::Vector2f(244, 71), sf::Vector2f(1218, 1137))
	};

	// LEVEL 3 DAY
	m_platforms[4] = {
		//new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 865.f), sf::Vector2f(0.f, 940.f)),

		new StaticPhysicsObject(sf::Vector2f(147, 147), sf::Vector2f(152, 954)),
		new StaticPhysicsObject(sf::Vector2f(147, 135), sf::Vector2f(318, 1156)),
		new StaticPhysicsObject(sf::Vector2f(110, 96), sf::Vector2f(532, 1344)),
		new StaticPhysicsObject(sf::Vector2f(92, 94), sf::Vector2f(737, 1494)),
		new StaticPhysicsObject(sf::Vector2f(95, 87), sf::Vector2f(1015, 1602)),
		new StaticPhysicsObject(sf::Vector2f(133, 130), sf::Vector2f(1463, 855)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f))
	};

	m_hazards[4] = {
		new StaticPhysicsObject(sf::Vector2f(680, 54), sf::Vector2f(805, 1725))
	};

	// LEVEL 3 NIGHT
	m_platforms[5] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 845.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(173, 132), sf::Vector2f(311, 1580)),
		new StaticPhysicsObject(sf::Vector2f(185, 57), sf::Vector2f(637, 1743)),
		new StaticPhysicsObject(sf::Vector2f(272, 119), sf::Vector2f(1000, 1566)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(1600.f, 193.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(988.f, 320.f), sf::Vector2f(612.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(343.f, 554.f), sf::Vector2f(612.f, 0.f)),
		//new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};

	m_bouncePads[5] = {
		new StaticPhysicsObject(sf::Vector2f(100, 20), sf::Vector2f(1155, 1540))
	};

	// LEVEL 4 DAY
	m_platforms[6] = {
		//new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 865.f), sf::Vector2f(0.f, 940.f)),

		new StaticPhysicsObject(sf::Vector2f(150, 135), sf::Vector2f(280, 1665)),
		new StaticPhysicsObject(sf::Vector2f(150, 128), sf::Vector2f(707, 1310)),
		new StaticPhysicsObject(sf::Vector2f(155, 145), sf::Vector2f(1010, 771)),
		new StaticPhysicsObject(sf::Vector2f(141, 103), sf::Vector2f(1135, 1678)),
		new StaticPhysicsObject(sf::Vector2f(153, 155), sf::Vector2f(1487, 995)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f))
	};

	m_hazards[6] = {
		new StaticPhysicsObject(sf::Vector2f(115, 75), sf::Vector2f(722, 1238)),
		new StaticPhysicsObject(sf::Vector2f(115, 75), sf::Vector2f(1025, 700))
	};

	m_bouncePads[6] = {
		new StaticPhysicsObject(sf::Vector2f(150, 50), sf::Vector2f(280, 1617)),
		new StaticPhysicsObject(sf::Vector2f(130, 40), sf::Vector2f(1140, 1645))
	};

	// LEVEL 4 NIGHT
	m_platforms[7] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 845.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(190, 142), sf::Vector2f(285, 1635)),
		new StaticPhysicsObject(sf::Vector2f(422, 158), sf::Vector2f(595, 1157)),
		new StaticPhysicsObject(sf::Vector2f(185, 156), sf::Vector2f(1087, 1355)),
		new StaticPhysicsObject(sf::Vector2f(164, 143), sf::Vector2f(1400, 1127)),
		new StaticPhysicsObject(sf::Vector2f(164, 170), sf::Vector2f(1642, 895)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(1600.f, 193.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(988.f, 320.f), sf::Vector2f(612.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(343.f, 554.f), sf::Vector2f(612.f, 0.f)),
		//new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};

	m_hazards[7] = {
		new StaticPhysicsObject(sf::Vector2f(383, 35), sf::Vector2f(608, 1120))
	};

	m_bouncePads[7] = {
		new StaticPhysicsObject(sf::Vector2f(170, 50), sf::Vector2f(295, 1585))
	};

	// LEVEL 5 DAY
	m_platforms[8] = {
		//new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 775.f), sf::Vector2f(0.f, 1025.f)),

		new StaticPhysicsObject(sf::Vector2f(496, 125), sf::Vector2f(0.f, 934)),
		new StaticPhysicsObject(sf::Vector2f(127, 112), sf::Vector2f(700.f, 445)),
		new StaticPhysicsObject(sf::Vector2f(136, 121), sf::Vector2f(952, 346)),
		new StaticPhysicsObject(sf::Vector2f(155, 155), sf::Vector2f(1248, 500)),
		new StaticPhysicsObject(sf::Vector2f(143, 129), sf::Vector2f(1482, 674)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f))
	};

	m_hazards[8] = {
		new StaticPhysicsObject(sf::Vector2f(275, 40), sf::Vector2f(205, 895))
	};

	// LEVEL 5 NIGHT
	m_platforms[9] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(235.f, 845.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(143, 140), sf::Vector2f(267, 1626)),
		new StaticPhysicsObject(sf::Vector2f(165, 150), sf::Vector2f(446, 1620)),
		new StaticPhysicsObject(sf::Vector2f(170, 163), sf::Vector2f(680, 1600)),
		new StaticPhysicsObject(sf::Vector2f(186, 166), sf::Vector2f(925, 1462)),
		new StaticPhysicsObject(sf::Vector2f(202, 170), sf::Vector2f(1150, 1357)),
		new StaticPhysicsObject(sf::Vector2f(218, 202), sf::Vector2f(1400, 1163)),
		new StaticPhysicsObject(sf::Vector2f(192, 200), sf::Vector2f(1618, 927)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(1600.f, 193.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(988.f, 320.f), sf::Vector2f(612.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(343.f, 554.f), sf::Vector2f(612.f, 0.f)),
		//new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f)),
	};

	m_hazards[9] = {
		new StaticPhysicsObject(sf::Vector2f(115, 60), sf::Vector2f(465, 1555)),
		new StaticPhysicsObject(sf::Vector2f(148, 50), sf::Vector2f(957, 1408)),
		new StaticPhysicsObject(sf::Vector2f(154, 85), sf::Vector2f(1440, 1072))
	};

	m_bouncePads[9] = {
		new StaticPhysicsObject(sf::Vector2f(150, 40), sf::Vector2f(690, 1560)),
		new StaticPhysicsObject(sf::Vector2f(163, 50), sf::Vector2f(1170, 1305))
	};

	// GAME OVER :)
	m_platforms[10] = {
		new StaticPhysicsObject(sf::Vector2f(20.f, 1800.f), sf::Vector2f(-20.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(240.f, 875.f), sf::Vector2f(0.f, 955.f)),

		new StaticPhysicsObject(sf::Vector2f(246.f, 958.f), sf::Vector2f(1754.f, 842.f)),
		new StaticPhysicsObject(sf::Vector2f(2000.f, 140.f), sf::Vector2f(0.f, 0.f)),
		new StaticPhysicsObject(sf::Vector2f(20, 1800.f), sf::Vector2f(2000.f, 0.f))
	};

	m_bouncePads[10] =
	{
		new StaticPhysicsObject(sf::Vector2f(2000.f, 100.f), sf::Vector2f(0.f, 1600.f))
	};
}

////////////////////////////////////////////////////////////

void Game::loadTextures()
{
	m_textureIDs = {
		"level1_day",
		"level1_night",
		"level2_day",
		"level2_night",
		"level3_day",
		"level3_night",
		"level4_day",
		"level4_night",
		"level5_day",
		"level6_night",
		"endScreen"
	};

	auto tm = TextureManager::getInstance();
	tm->loadTexture(m_textureIDs.at(0), "assets/images/level1Day.png");
	tm->loadTexture(m_textureIDs.at(1), "assets/images/level1Night.png");
	tm->loadTexture(m_textureIDs.at(2), "assets/images/level2DAY.png");
	tm->loadTexture(m_textureIDs.at(3), "assets/images/level2NIGHT.png");
	tm->loadTexture(m_textureIDs.at(4), "assets/images/level3DAY.png");
	tm->loadTexture(m_textureIDs.at(5), "assets/images/level3NIGHT.png");
	tm->loadTexture(m_textureIDs.at(6), "assets/images/level4DAY.png");
	tm->loadTexture(m_textureIDs.at(7), "assets/images/level4NIGHT.png");
	tm->loadTexture(m_textureIDs.at(8), "assets/images/level5DAY.png");
	tm->loadTexture(m_textureIDs.at(9), "assets/images/level5NIGHT_END.png");
	tm->loadTexture(m_textureIDs.at(10), "assets/images/endScreen.png");

	tm->loadTexture("player", "assets/images/Running_SpriteHorizontal.png");
}

////////////////////////////////////////////////////////////

void Game::loadAudio()
{
	m_backgroundMusic.openFromFile("assets/audio/quantum_leap.wav");
	m_deathSoundBuffer.loadFromFile("assets/audio/death.wav");
	m_deathSound.setBuffer(m_deathSoundBuffer);
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
			case sf::Keyboard::Num0:
				loadLevel(0);
				break;
			case sf::Keyboard::Num1:
				loadLevel(1);
				break;
			case sf::Keyboard::Num2:
				loadLevel(2);
				break;
			case sf::Keyboard::Num3:
				loadLevel(3);
				break;
			case sf::Keyboard::Num4:
				loadLevel(4);
				break;
			case sf::Keyboard::Num5:
				loadLevel(5);
				break;
			case sf::Keyboard::Num6:
				loadLevel(6);
				break;
			case sf::Keyboard::Num7:
				loadLevel(7);
				break;
			case sf::Keyboard::Num8:
				loadLevel(8);
				break;
			case sf::Keyboard::Num9:
				loadLevel(9);
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

	for (auto platform : *p_currentPlatforms)
	{
		if (CollisionChecker::circleToAABB(platform->getBody(), m_player->getCollider()))
		{
			m_player->allowJump();
			
			CollisionResolver::resolvePlayerPlatform(m_player, platform);
		}
	}

	for (auto hazard : *p_currentHazards)
	{
		if (CollisionChecker::circleToAABB(hazard->getBody(), m_player->getCollider()))
		{
			m_deathSound.play();
			loadLevel(m_currentLevel);
		}
	}

	for (auto bouncepad : *p_currentBouncePads)
	{
		if (CollisionChecker::circleToAABB(bouncepad->getBody(), m_player->getCollider()))
		{
			m_player->bounce();
		}
	}

	if (m_transitioning)
		transition();

	auto p = *m_player->getPhysicsBody()->getPosition();

	// Advance
	if (p.x < 0.f || p.x > 2000.f)
		loadLevel(++m_currentLevel);
	// Reset
	else if (p.y > 2000.f)
	{
		m_deathSound.play();
		loadLevel(m_currentLevel);
	}
}

////////////////////////////////////////////////////////////

void Game::transition()
{
	static bool started{ false };
	static sf::Clock c;

	// Restart our clock
	if (!started)
	{
		c.restart();
		started = !started;
	}

	unsigned alpha;

	if (c.getElapsedTime() < sf::seconds(0.45f))
	{
		// 0 to 255 to 0 in 0.45 seconds
		float coefficient = (90 + c.getElapsedTime().asSeconds() * 200) * MathUtils::deg2rad;
		alpha = 255 * (sinf(coefficient));
	}
	else
	{
		m_transitioning = false;
		started = !started;
		return;
	}

	m_magicTransitionRectangle.setFillColor(sf::Color(0, 0, 0, alpha));
}

////////////////////////////////////////////////////////////

void Game::render()
{
	m_window->clear(sf::Color::Black);

	m_window->draw(m_background);

	m_player->draw(*m_window);

	//for (auto hazard : *p_currentHazards)
	//{
	//	m_window->draw(*hazard->getBody());
	//}

	//for (auto bouncepad : *p_currentBouncePads)
	//{
	//	m_window->draw(*bouncepad->getBody());
	//}

	m_window->draw(m_magicTransitionRectangle);

	m_window->display();
}


///////////////////////////////////////////////////////////////////////////////

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title, sf::Style::Titlebar | sf::Style::Close);
}
