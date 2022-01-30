#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPITE_G

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "PhysicsBody.h"

class AnimatedSprite
{
public:
	AnimatedSprite(sf::Texture* t_texture = nullptr);
	~AnimatedSprite();

	void setTexture(sf::Texture* t_texture) { m_texture = t_texture; m_sprite.setTexture(*t_texture); }
	void setFrames(std::vector<sf::IntRect> t_frames);
	void setFrameDelay(sf::Time t_timePerFrame) { m_timePerFrame = t_timePerFrame; }
	void setAnimationSpeed(float t_speed);
	void setScale(sf::Vector2f t_scale) { m_sprite.setScale(t_scale);}
	void setOrigin(sf::Vector2f t_origin) { m_sprite.setOrigin(t_origin); }
	sf::FloatRect getGlobalBounds() { return m_sprite.getGlobalBounds(); }

	void loop(bool t_shouldLoop) { m_loop = t_shouldLoop; }

	void setPosition(sf::Vector2f t_pos) { m_sprite.setPosition(t_pos); }

	void update();

	void draw(sf::RenderWindow& t_renderer);

private:
	sf::Texture* m_texture{ nullptr };
	sf::Sprite m_sprite;
	std::vector<sf::IntRect>::iterator m_currentFrame;

	std::vector<sf::IntRect> m_frames;

	bool m_loop{ true };

	sf::Clock m_clock;
	sf::Time m_timePerFrame{ sf::seconds(0.2f) };
};

#endif