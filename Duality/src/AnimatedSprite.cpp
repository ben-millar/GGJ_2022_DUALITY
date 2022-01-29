#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture* t_texture) :
	m_texture{ t_texture }
{
	m_clock.restart();
	m_sprite.setScale({ 0.6f, 0.6f });
}

////////////////////////////////////////////////////////////

AnimatedSprite::~AnimatedSprite()
{
}

////////////////////////////////////////////////////////////

void AnimatedSprite::setFrames(std::vector<sf::IntRect> t_frames)
{
	m_frames = t_frames;
	m_currentFrame = m_frames.begin();
	m_sprite.setTextureRect(*m_currentFrame);
	m_clock.restart();
}

////////////////////////////////////////////////////////////

void AnimatedSprite::setAnimationSpeed(float t_speed)
{
	static sf::Time minDelay{ sf::seconds(0.1f) };
	static sf::Time maxDelay{ sf::seconds(0.5f) };

	auto delay = (t_speed)
		? minDelay + (maxDelay - minDelay) * (1-t_speed)
		: sf::seconds(180.f);

	setFrameDelay(delay);
}

////////////////////////////////////////////////////////////

void AnimatedSprite::update()
{
	if (m_clock.getElapsedTime() > m_timePerFrame)
	{
		if (m_frames.end() == ++m_currentFrame)
		{
			if (m_loop)
				m_currentFrame = m_frames.begin();
			else
				--m_currentFrame;
		}

		m_sprite.setTextureRect(*m_currentFrame);

		m_clock.restart();
	}
}

////////////////////////////////////////////////////////////

void AnimatedSprite::draw(sf::RenderWindow& t_renderer)
{
	t_renderer.draw(m_sprite);
}
